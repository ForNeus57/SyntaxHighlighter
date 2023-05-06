$directory = ".\tests\input\c_programs"  # Replace with the actual directory path

# Get all files in the directory with a specific extension, e.g., .txt
$files = Get-ChildItem -Path $directory -Filter "*.c"

foreach ($file in $files) {
    # Build the input and output file paths
    $inputFile = $file.FullName
    $outputFile = $file.FullName -replace "\.c$", "_out.html"

    # Run the program with the input and output file arguments
    Start-Process -FilePath ".\Syntax_Colorizer.exe" -ArgumentList "$inputFile", "$outputFile" -Wait
}