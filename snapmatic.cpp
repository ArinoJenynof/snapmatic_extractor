#include <print>
#include <filesystem>
#include <array>
#include <fstream>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::println("Usage: snapmatic <output folder>");
		std::println("\t<output folder>\tFolder to place extracted JPGs");
		return -1;
	}

	const std::filesystem::path userprofile { std::getenv("USERPROFILE") };
	const std::filesystem::path outdir { argv[1] };
	const std::array profile_dirs {
		userprofile / "Documents" / "Rockstar Games" / "GTA V" / "Profiles",
		userprofile / "Documents" / "Rockstar Games" / "GTAV Enhanced" / "Profiles"
	};

	std::error_code ec {};
	std::filesystem::create_directories(outdir, ec);
	for (const std::filesystem::path& profile_dir : profile_dirs)
	{
		std::println("Searching {}", profile_dir.string());
		for (const std::filesystem::directory_entry& profile_id : std::filesystem::directory_iterator(profile_dir, ec))
		{
			std::println("\tFound profile {}", profile_id.path().filename().string());
			for (const std::filesystem::directory_entry& e : std::filesystem::directory_iterator(profile_id, ec))
			{
				if (e.path().filename().string().substr(0, 4) == "PGTA")
				{
					const std::filesystem::path outfile { outdir / (e.path().filename().string() + ".jpg") };
					std::println("\t\tExtracting to {}", outfile.string());

					std::ifstream snap_inp(e.path(), std::ios::binary);
					std::ofstream snap_out(outfile, std::ios::binary);

					// Bytes 0-291 are Rockstar's metadata, possibly date taken and latitude longitude
					snap_inp.seekg(292);
					snap_out << snap_inp.rdbuf();
				}
			}
		}
	}

	return 0;
}
