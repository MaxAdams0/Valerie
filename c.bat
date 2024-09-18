@echo on
:: @echo .png to .c/.h conversion (empty if up to date)
:: for %%f in (.\res\*.png) do png2asset %%f -spr8x8
png2asset .\res\text_set.png -map -spr8x8 -no_palettes -noflip

:: compile all c and h into gb binary
C:\gbdk\bin\lcc.exe -o ValkCP.gb src/*.c res/*.c -Wm-yC
timeout /t 10 /nobreak
cls