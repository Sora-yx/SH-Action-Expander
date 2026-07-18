# Set Working Directory
Split-Path $MyInvocation.MyCommand.Path | Push-Location
[Environment]::CurrentDirectory = $PWD

Remove-Item "$env:RELOADEDIIMODS/Action_Expander/*" -Force -Recurse
dotnet publish "./Action_Expander.csproj" -c Release -o "$env:RELOADEDIIMODS/Action_Expander" /p:OutputPath="./bin/Release" /p:ReloadedILLink="true"

# Restore Working Directory
Pop-Location