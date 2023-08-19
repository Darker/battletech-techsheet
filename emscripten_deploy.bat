cmake --build . --target techsheet_cli
if NOT %ERRORLEVEL% == 0 goto :endofscript
copy .\techsheet_cli.js ..\..\web\root\techsheet_cli.js
copy .\techsheet_cli.wasm ..\..\web\root\techsheet_cli.wasm

:endofscript