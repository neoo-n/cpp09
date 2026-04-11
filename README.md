The last 3 exercices in CPP. For the whole CPP, you need to use the STL.

The first two exercices must use at least 1 container. The last one need at least two.
Each of this container must be different.

## Ex00
This exercice requires you to use a `data.csv` file and to take an input file (`input.txt` for example).

### Required files 
The `data.csv` is a file containing a date and an exchange rate. It should look like this :
```
date,exchange_rate
xxxx-xx-xx,x
xxxx-xx-xx,x
xxxx-xx-xx,x
xxxx-xx-xx,x
xxxx-xx-xx,x
xxxx-xx-xx,x
xxxx-xx-xx,x
```
The date is on the left with the yyyy-mm-dd (year-month-day) format and on the right is the value.

The input file contains a date and a value. It should look like this :
```
date | value
xxxx-xx-xx | x
xxxx-xx-xx | x
xxxx-xx-xx | x
xxxx-xx-xx | x
```
The date is on the left with the yyyy-mm-dd (year-month-day) format and on the right is the value.

The value can neither be lower than 0 nor greater than 1000.

### Project structure

I used the map container to store all the data.csv, date as key and exchange rate as value.

The exercice asks you to find the exact date or the closest lower date of your input
