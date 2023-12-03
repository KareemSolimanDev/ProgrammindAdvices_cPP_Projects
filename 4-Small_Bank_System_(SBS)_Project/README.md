# Small_Bank_System_(SBS)_Project

### Project versions & functions
<hr>

1. #### V: 1.1
    1. dashboard to show all clients .
    2. add clients.
    3. search in clients.
    4. update clients.
    5. delete clients.

2. #### V: 2.0
    1. deposite to client account.  
    2. withdraw from client account.  
    3. small dashboard with total balances.

3. #### V: 3.0
    1. improve code and fix some errors.  
    2. add links to navigate among pages.  

4. #### V: 4.9
    1. login screen for admins.
    2. handel admin permitions.
    3. add admins based on permetions.
    4. search in admins based on permetions.
    5. update admins based on permetions.
    6. delete admins based on permetions.  

<hr>
<hr>

### Project notes
<hr>

1. In this project i will use a library(./myCode/libs/helpers.h) from my creation for geniric functions.

2. use libraries to make code like **Flask**(backend framework based in python) logic.

3. in ./myCode/libs/mainFuncs.h(LoadClientData() function) i store functions result in variable instead of send functions as a parameter to save stack memory.

4. in ./myCode/libs/mainFuncs.h(DeleteClient() and UpdateClient() functions) i can gather them in one function because they have alot of repeted code to apply DRY(Donot Repeat Yourself) but this will kill SRP(Single Responsapility Prinsiple) so i decided to use SRP to make code easy to understand, maintain, and extend (i found Command pattern while search that can solve DRY and SRP maybe i will learn it later).

5. in note(4) i preferd to seprate functions, now in ./myCode/libs/mainFuncs.h(Transaction() function) i used another style to apply DRY ,so i gather Deposite() and Withdraw() in one function(Transaction() function).

6. in V:4.9 when i try to add admin file name to config file to use it in mainFunc file i faced problem , after fighting with code and changing the path of file i solve it
so there is a problem explanation:

    ##### files structur:
    ```
    myCode/
        db/
            admin_data.txt
        libs/
            config.h
            mainFunc.h
        run.cpp
    ```
    i want to reach admin_data.txt from config.h so it is supposed to be '../db/admin_data.txt' but the path must depend on executable's location(exe file) like 'db/admin_data.txt'.

^_^