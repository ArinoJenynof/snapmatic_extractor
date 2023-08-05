#include <cstdlib>
#include <fstream>
#include <filesystem>

int main()
{
	namespace fs = std::filesystem;
	const fs::path userprofile = std::getenv("USERPROFILE");
	const fs::path rgsc = userprofile / "Documents\\Rockstar Games\\GTA V\\Profiles";

	for (const fs::directory_entry &profile : fs::directory_iterator(rgsc))
	{
		const fs::path outdir = profile.path().filename();
		fs::create_directory(outdir);

		for (const fs::directory_entry &dirent : fs::directory_iterator(profile))
		{
			const fs::path filename = dirent.path().filename();
			if (filename.string().substr(0, 4) == "PGTA")
			{
				const fs::path outfile = filename.string() + ".jpg";

				std::ifstream inp(dirent.path(), std::ios::binary);
				std::ofstream out(outdir / outfile, std::ios::binary);

				inp.seekg(292);
				out << inp.rdbuf();
			}
		}
	}

	return 0;
}