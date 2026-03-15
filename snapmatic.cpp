#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>

int main()
{
	using namespace std::filesystem;

	const path USERPROFILE { std::getenv("USERPROFILE") };
	const std::array profile_dirs {
		USERPROFILE / "Documents" / "Rockstar Games" / "GTA V" / "Profiles",
		USERPROFILE / "Documents" / "Rockstar Games" / "GTAV Enhanced" / "Profiles"
	};

	for (const path& profile_dir : profile_dirs)
	{
		for (const directory_entry& profile : directory_iterator { profile_dir })
		{
			std::error_code ec {};
			const path outdir { profile.path().filename() };
			create_directories(outdir, ec);

			for (const directory_entry& pic : directory_iterator { profile })
			{
				if (pic.path().filename().string().substr(0, 4) == "PGTA")
				{
					const path outfile { outdir / (pic.path().filename().string() + ".jpg") };
					if (exists(outfile, ec))
						continue;
					const path infile { pic.path() };

					std::ifstream snap_in { infile, std::ios::binary };
					std::ofstream snap_out { outfile, std::ios::binary };
					snap_in.seekg(292);
					snap_out << snap_in.rdbuf();
				}
			}
		}
	}

	return 0;
}
