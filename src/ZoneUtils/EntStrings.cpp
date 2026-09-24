#include "stdafx.hpp"

#include "GSC.hpp"
namespace mapents::converter::iw5
{
	std::string convert_mapents_ids(const std::string& source)
	{
		std::string out_buffer;

		const auto lines = split(source, '\n');

		for (auto i = 0; i < lines.size(); i++)
		{
			const auto& line = lines[i];

			std::regex expr(R"~((.+) "(.*)")~");
			std::smatch match{};
			if (!line.starts_with("0 ") && std::regex_search(line, match, expr))
			{
				const auto token = match[1].str();

				const auto has_digit = token.find_first_of("0123456789") != std::string::npos;
				const auto has_other = token.find_first_not_of("0123456789 \t") != std::string::npos;
				if (!has_digit || has_other)
				{
					out_buffer.append(line);
					out_buffer.append("\n");
					continue;
				}

				const auto id = std::atoi(token.data());
				const auto value = match[2].str();

				std::string key = gsc::iw5::gsc_ctx->token_name(
					static_cast<std::uint16_t>(id));
				if (!key.empty() && !key.starts_with("_id_"))
				{
					out_buffer.append(va("\"%s\" \"%s\"", key.data(), value.data()));
					out_buffer.append("\n");
					continue;
				}
				else
				{
					out_buffer.append("//" + line);
					out_buffer.append("\n");
					continue;
				}
			}
			out_buffer.append(line);
			out_buffer.append("\n");
		}

		return out_buffer;
	}
}

namespace mapents2spawns
{
	SpawnPointList* generate_spawnpoint_list(char* entity_string)
	{
		SpawnPointList* list = new SpawnPointList;
		list->num_spawns = 0;
		list->spawns = new SpawnPoint[MAX_SPAWNS];
		memset(list->spawns, 0, sizeof(SpawnPoint) * MAX_SPAWNS);

		char* ents = entity_string;

		bool in_brackets = false;
		bool in_comma = false;
		bool in_comment = false;
		int line = 1;
		int col = 1;

		bool reading_value = false;
		std::string id;
		std::string value;
		std::vector<std::pair<std::string, std::string>> values;

		auto increment = [&]()
		{
			ents++;
			col++;
		};

		auto linebreak = [&]()
		{
			ents++;
			line++;
			col = 1;
		};

		auto add_spawnent = [&]()
		{
			if (list->num_spawns == MAX_SPAWNS)
			{
				throw std::runtime_error("mapents error: too many spawns, increase MAX_SPAWNS");
			}

			list->spawns[list->num_spawns].name = "";
			list->spawns[list->num_spawns].target = "";
			list->spawns[list->num_spawns].script_noteworthy = "";
			list->spawns[list->num_spawns].unknown = "";

			for (auto value : values)
			{
				if (value.first == "classname")
				{
					list->spawns[list->num_spawns].name = _strdup(value.second.data());
				}
				else if (value.first == "target")
				{
					list->spawns[list->num_spawns].target = _strdup(value.second.data());
				}
				else if (value.first == "script_noteworthy")
				{
					list->spawns[list->num_spawns].script_noteworthy = _strdup(value.second.data());
				}
				else if (value.first == "origin")
				{
					std::vector<std::string> tokens;
					std::stringstream check1(value.second);
					std::string intermediate;
					while (getline(check1, intermediate, ' '))
					{
						tokens.push_back(intermediate);
					}
					if (tokens.size() < 3)
					{
						if (!tokens.size())
						{
							// fixup to (0,0,0)
							for (auto i = 0; i < 3; i++)
								tokens.push_back("0");
						}
						else
						{
							throw std::runtime_error(va("mapents error: origin got fucked, line: %d", line));
						}
					}
					for (auto i = 0; i < 3; i++)
					{
						list->spawns[list->num_spawns].origin[i] = static_cast<float>(atof(tokens[i].data()));
					}
				}
				else if (value.first == "angles")
				{
					std::vector<std::string> tokens;
					std::stringstream check1(value.second);
					std::string intermediate;
					while (getline(check1, intermediate, ' '))
					{
						tokens.push_back(intermediate);
					}
					if (tokens.size() < 3)
					{
						if (!tokens.size())
						{
							// fixup to (0,0,0)
							for (auto i = 0; i < 3; i++)
								tokens.push_back("0");
						}
						else
						{
							throw std::runtime_error(va("mapents error: angles got fucked, line: %d", line));
						}
					}
					for (auto i = 0; i < 3; i++)
					{
						list->spawns[list->num_spawns].angles[i] = static_cast<float>(atof(tokens[i].data()));
					}
				}
			}

			list->num_spawns++;
		};

		auto check_spawnent = [&]()
		{
			bool valid = false;
			for (auto value : values)
			{
				if (value.first == "classname")
				{
					if (value.second.find("mp_") != std::string::npos && value.second.find("_spawn") != std::string::npos)
					{
						valid = true;
						break;
					}
				}
				if (valid)
				{
					break;
				}
			}
			if (valid)
			{
				add_spawnent();
			}
		};

		while (*ents != '\0')
		{
			if (*ents == '/' && ents[1] == '/')
			{
				in_comment = true;
			}
			if (*ents == '\n')
			{
				if (in_comment)
				{
					in_comment = false;
				}

				linebreak();
				continue;
			}
			if (in_comment)
			{
				increment();
				continue;
			}
			if (*ents == '{')
			{
				if (in_brackets)
				{
					throw std::runtime_error(va("mapents error: %c\nline: %d, col: %d\n%s", *ents, line, col, "bracket start inside another bracket"));
					return nullptr;
				}
				in_brackets = true;
				increment();
				continue;
			}
			if (*ents == '}')
			{
				if (!in_brackets)
				{
					throw std::runtime_error(va("mapents error: %c\nline: %d, col: %d\n%s", *ents, line, col, "unexpected bracket end"));
					return nullptr;
				}

				check_spawnent();
				values.clear();

				in_brackets = false;
				increment();
				continue;
			}
			if (!in_brackets)
			{
				increment();
				continue;
				//throw std::runtime_error(va("mapents error: %c\nline: %d, col: %d\n%s", *ents, line, col, "no brackets found"));
				//return nullptr;
			}
			if (*ents == ' ')
			{
				if (!in_comma)
				{
					increment();
					continue;
				}
			}
			if (*ents == '"')
			{
				if (in_comma)
				{
					if (reading_value)
					{
						values.push_back({ id, value });
						id.clear();
						value.clear();
					}
					reading_value = !reading_value;
					in_comma = false;
					increment();
					continue;
				}
				else
				{
					in_comma = true;
					increment();
					continue;
				}
			}
			if (!in_comma)
			{
				increment();
				continue;
				//throw std::runtime_error(va("mapents error: %c\nline: %d, col: %d\n%s", *ents, line, col, "no comma found"));
				//return nullptr;
			}
			if (!reading_value)
			{
				id.push_back(*ents);
				increment();
				continue;
			}
			else
			{
				value.push_back(*ents);
				increment();
				continue;
			}
		}

		return list;
	}

	void dump_spawnpoint_list(const std::string& output, SpawnPointList* list)
	{
		FILE* fp;
		const auto path = output;
		auto file = fopen_s(&fp, path.data(), "wb");

		if (!fp)
		{
			throw std::runtime_error(va("failed to open file \"%s\" for write", path.data()));
		}

		nlohmann::ordered_json data;

		for (int i = 0; i < list->num_spawns; i++)
		{
			data[i]["name"] = list->spawns[i].name;
			data[i]["target"] = list->spawns[i].target;
			data[i]["script_noteworthy"] = list->spawns[i].script_noteworthy;
			data[i]["unknown"] = list->spawns[i].unknown;
			for (auto j = 0; j < 3; j++)
			{
				data[i]["origin"][j] = list->spawns[i].origin[j];
				data[i]["angles"][j] = list->spawns[i].angles[j];
			}
		}

		const auto json = data.dump(4);
		fwrite(json.data(), json.size(), 1, fp);

		fclose(fp);
	}

	void dump_spawns(const std::string& out, char* entity_string)
	{
		try
		{
			auto* spawn_list = mapents2spawns::generate_spawnpoint_list(entity_string);
			if (spawn_list)
			{
				if (spawn_list->num_spawns)
				{
					dump_spawnpoint_list(out, spawn_list);
				}

				delete[] spawn_list->spawns;
				delete spawn_list;
			}
		}
		catch(std::runtime_error& err)
		{
			ZONETOOL_FATAL("entstrings.cpp\n%s", err.what());
		}
	}
}