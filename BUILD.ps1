# u can use this script to compile the project for release to both steam and gog
# releases will be created as zip archives
# script will clean up the build directories after the releases are created

param (
    [switch]$Clean
)

if ($Clean) {
    write-host "cleaning old build directories..."
    if (test-path build_steam) { remove-item -recurse -force build_steam }
    if (test-path build_gog) { remove-item -recurse -force build_gog }
}

$dirsToRemove = @("temp_Release_Steam", "temp_Release_GOG", "temp_ExampleMod", "temp_Debug_Steam", "temp_Debug_GOG", "temp_ExampleMod_Debug")
foreach ($d in $dirsToRemove) { if (test-path $d) { remove-item -recurse -force $d } }

$zipsToRemove = @("Release_Steam.zip", "Release_GOG.zip", "ExampleMod.zip", "Debug_Steam.zip", "Debug_GOG.zip", "ExampleMod_Debug.zip")
foreach ($z in $zipsToRemove) { if (test-path $z) { remove-item -force $z } }

if (!(test-path build_steam)) {
    write-host "configuring steam build..."
    cmake -B build_steam -DSTEAM_PLATFORM=ON
}
if (!(test-path build_gog)) {
    write-host "configuring gog build..."
    cmake -B build_gog -DSTEAM_PLATFORM=OFF
}

write-host "compiling steam (Release)..."
cmake --build build_steam --config RelWithDebInfo
if ($LASTEXITCODE -ne 0) { write-error "steam release build failed"; exit 1 }

write-host "compiling steam (Debug)..."
cmake --build build_steam --config Debug
if ($LASTEXITCODE -ne 0) { write-error "steam debug build failed"; exit 1 }

write-host "compiling gog (Release)..."
cmake --build build_gog --config RelWithDebInfo
if ($LASTEXITCODE -ne 0) {
    if (!(test-path build_gog/DyingLightGame/RelWithDebInfo/DyingLightGame.exe)) { write-error "gog release build failed"; exit 1 }
}

write-host "compiling gog (Debug)..."
cmake --build build_gog --config Debug
if ($LASTEXITCODE -ne 0) {
    if (!(test-path build_gog/DyingLightGame/Debug/DyingLightGame.exe)) { write-error "gog debug build failed"; exit 1 }
}

foreach ($d in $dirsToRemove) { new-item -itemtype directory -path $d | out-null }

function Copy-BuildFiles($buildDir, $config, $gameTargetDir, $modTargetDir) {
    $exePath = "$buildDir/DyingLightGame/$config/DyingLightGame.exe"
    $exePdbPath = "$buildDir/DyingLightGame/$config/DyingLightGame.pdb"
    $exeLibPath = "$buildDir/DyingLightGame/$config/DyingLightGame.lib"
    $exeExpPath = "$buildDir/DyingLightGame/$config/DyingLightGame.exp"

    $modDllPath = "$buildDir/ExampleMod/$config/ExampleMod.dll"
    $modPdbPath = "$buildDir/ExampleMod/$config/ExampleMod.pdb"
    $modLibPath = "$buildDir/ExampleMod/$config/ExampleMod.lib"
    $modExpPath = "$buildDir/ExampleMod/$config/ExampleMod.exp"

    if ($gameTargetDir -and (test-path $exePath)) { copy-item $exePath $gameTargetDir }
    if ($gameTargetDir -and (test-path $exePdbPath)) { copy-item $exePdbPath $gameTargetDir }
    if ($gameTargetDir -and (test-path $exeLibPath)) { copy-item $exeLibPath $gameTargetDir }
    if ($gameTargetDir -and (test-path $exeExpPath)) { copy-item $exeExpPath $gameTargetDir }

    if ($modTargetDir -and (test-path $modDllPath)) { copy-item $modDllPath $modTargetDir }
    if ($modTargetDir -and (test-path $modPdbPath)) { copy-item $modPdbPath $modTargetDir }
    if ($modTargetDir -and (test-path $modLibPath)) { copy-item $modLibPath $modTargetDir }
    if ($modTargetDir -and (test-path $modExpPath)) { copy-item $modExpPath $modTargetDir }
}

write-host "copying build files..."
Copy-BuildFiles "build_steam" "RelWithDebInfo" "temp_Release_Steam" "temp_ExampleMod"
Copy-BuildFiles "build_steam" "Debug" "temp_Debug_Steam" "temp_ExampleMod_Debug"

Copy-BuildFiles "build_gog" "RelWithDebInfo" "temp_Release_GOG" $null
Copy-BuildFiles "build_gog" "Debug" "temp_Debug_GOG" $null

write-host "creating zip archives..."
foreach ($d in $dirsToRemove) {
    $zipName = $d.Replace("temp_", "") + ".zip"
    compress-archive -path "$d/*" -destinationpath $zipName -force
    remove-item -recurse -force $d
}

write-host "packaging complete."