# Small_Bank_System_(SBS)_Project

### Project notes
<hr>

1. In this project i will use a library from my creation for geniric functions.
2. use libraries to make code mantainable use some flask(backend framework based in python) logic.
3. in libs/mainFuncs.h(LoadClientData() function) i store functions result in variable instead of send functions as a parameter to save stack memory.
4. in libs/mainFuncs.h(DeleteClient() and UpdateClient() functions) i can gather them in one function because they have alot of repeted code to apply DRY(Donot Repeat Yourself) but this will kill SRP(Single Responsapility Prinsiple) so i decided to use SRP to make code easy to understand, maintain, and extend (i found Command pattern while search that can solve DRY and SRP maybe i will learn it later).