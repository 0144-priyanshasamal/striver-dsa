param(
    [Parameter(Mandatory=$false)]
    [string]$Message = "Update solution"
)

$SourceDir = "c:\DSA\GRAPH"
$DestDir = "C:\gitclone\striver-dsa\GRAPH"

# Ensure the destination directory exists
if (!(Test-Path -Path $DestDir)) {
    New-Item -ItemType Directory -Path $DestDir -Force | Out-Null
}

Write-Host "1. Copying files to main repository..." -ForegroundColor Cyan
Get-ChildItem -Path $SourceDir -Exclude ".git", "deposit.ps1" | ForEach-Object {
    Copy-Item -Path $_.FullName -Destination $DestDir -Force -Recurse
}

Write-Host "2. Navigating to main repository..." -ForegroundColor Cyan
Push-Location "C:\gitclone\striver-dsa"

try {
    Write-Host "3. Staging files..." -ForegroundColor Cyan
    git add .

    Write-Host "4. Committing with message: '$Message'..." -ForegroundColor Cyan
    git commit -m $Message

    Write-Host "5. Pushing to GitHub..." -ForegroundColor Cyan
    git push origin main

    Write-Host "`nSuccessfully deposited to GitHub! 🎉" -ForegroundColor Green
}
catch {
    Write-Error "Git operations failed."
}
finally {
    Pop-Location
}
