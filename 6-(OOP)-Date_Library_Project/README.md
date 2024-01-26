# (OOP) Date_Library_Project

### How it work
<hr>
create object from clsDate class then use non_static functions or static functions.

#### example :

```cpp
    clsDate d1;// create date object
    d1.Print();// print now date

    cout << d1.getDay();// use functions like that

    clsDate::IsLeap(2024);// use static functions

```

### Project notes
<hr>

0. in learning vhase i focus my attention on code not documntation.
1. In this project i use simple OOP paradigm.
2. Every function documented by her name.
3. make 4 ways to define object from class.
    ```cpp
    // 1. donot take any parameters so it print now date
    clsDate d1;
    d1.Print();

    // 2. take date as (day ,month , year) and print it
    clsDate d2(1,1,2024);
    d2.Print();

    // 3. take date as (day order in year, year) then format it print it
    clsDate d3(33,2023);
    d3.Print();

    // 4. take date as string then format it and print it
    clsDate d4("29/12/2014");
    d4.Print();
    ```
4. in this project static functions is only functions that return value.
5. for more advanced date problems visit : [Date functions repo](https://github.com/kemooalsayd/programmingAdvices_problemSolving_level_4)
6. <b>!mportant note :</b> this code on learning vhase and all functions made by me before watching solution.

<hr>


# <b>^_^</b>