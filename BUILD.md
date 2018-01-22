# BrabeNetz - Build Instructions

You can build BrabeNetz on 3 different ways, choose one:


1. Use [NuGet](https://www.nuget.org/packages/BrabeNetz) _(recommended)_
	1. Open your Visual Studio C++ Project
	2. Navigate to `Tools`>`NuGet Package Manager`>`Manage NuGet Packages for Solution`
	3. Search for **"BrabeNetz"**
	4. Click **install**

2. Download pre-built
	1. Go to [releases](https://github.com/mrousavy/BrabeNetz/releases/latest)
	2. Download latest pre-built binaries `.zip`
	3. **Extract** zip in your Solution
	4. Go to your Visual Studio Project's **Properties**
	5. Add path to `headers` to `Properties`>`C/C++`>`General`>`Additional include Directories` (should look like `$(SolutionDir)headers;%(AdditionalIncludeDirectories)`)
	6. Add path to `lib` to `Properties`>`Linker`>`General`>`Additional library Directories` (should look like `$(SolutionDir)lib;%(AdditionalLibraryDirectories)`)
	7. Add `"BrabeNetz.lib"` for Configuration **Debug**, and `BrabeNetz_d.lib` for **Release**, to `Properties`>`Linker`>`Input`>`Additional Dependencies` (should look like `BrabeNetz.lib;%(AdditionalDependencies)` or `BrabeNetz_d.lib;%(AdditionalDependencies)`)

3. Manually
	1. Clone from GitHub: `git clone http://github.com/mrousavy/BrabeNetz`
	2. Open [Developer Commandprompt for Visual Studio](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs) and navigate to the `BrabeNetz\BrabeNetz` folder
	3. Run `msbuild BrabeNetz.vcxproj /p:Configuration=Release /p:Platform=x64` (Use the configuration and platform you need)
	4. Output files are now in `BrabeNetz\x64` or `BrabeNetz\Win32`
	5. Go to your Visual Studio Project's **Properties**
	6. Add path to `headers` to `Properties`>`C/C++`>`General`>`Additional include Directories` (should look like `$(SolutionDir)headers;%(AdditionalIncludeDirectories)`)
	7. Add path to `lib` to `Properties`>`Linker`>`General`>`Additional library Directories` (should look like `$(SolutionDir)lib;%(AdditionalLibraryDirectories)`)
	8. Add `"BrabeNetz.lib"` for Configuration **Debug**, and `BrabeNetz_d.lib` for **Release**, to `Properties`>`Linker`>`Input`>`Additional Dependencies` (should look like `BrabeNetz.lib;%(AdditionalDependencies)` or `BrabeNetz_d.lib;%(AdditionalDependencies)`)
