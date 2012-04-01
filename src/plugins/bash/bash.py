#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os

def setupSettings (settings):
	# получаем имя файла настройки ~/.bashrc
	name = os.path.expanduser("~/.bashrc")
	bashrc = open(name, "a")
	# пишем все в конец файла и расставляем метки для удаления
	bashrc.write("\n#syrop begin\n")
	# если http_proxy уже установлен, но пропускаем его, но выводим сообщение
	# пользователь пусть сам разбирается с уже установленными значениями
	if not ("http_proxy" in os.environ):
		if "http" in settings:
			bashrc.write("http_proxy=" + settings["http"] + "\n")
			bashrc.write("export http_proxy\n")
	else:
		print "WARN: http_proxy is set already in ", os.environ["http_proxy"]
	
	# аналогично для https
	if not ("https_proxy" in os.environ):
		if "https" in settings:
			bashrc.write("https_proxy=" + settings["https"] + "\n")
			bashrc.write("export https_proxy\n")
	else:
		print "WARN: https_proxy is set already in ", os.environ["https_proxy"]
	# ставим конечную метку
	bashrc.write("\n#syrop end\n")
	bashrc.close()

def cleanupSettings ():
	name = os.path.expanduser("~/.bashrc")
	# переименовываем bashrc
	os.rename(name, name + ".old")
	# открываем для чтения
	bashrcold = open(name + ".old", "r")
	# и создаем новый bashrc
	bashrcnew = open(name, "w")
	toDel = False
	# читаем построчно исходный bashrc
	for line in bashrcold.readlines():
		# если прочитанная строка совпадает с начальной меткой
		# значит начиная с этой строки и до конца файла или конечной метки
		# все строки должны быть удалены
		if line.strip(None) == "#syrop begin":
			toDel = True
		# если не в секции для удаления, то просто переписываем
		if not toDel:
			bashrcnew.write(line)
		# если прочитали конечную метку, то начиная с нее строки не удаляются
		if line.strip(None) == "#syrop end":
			toDel = False
	bashrcnew.close()
	bashrcold.close()
	# удаляем старый bashrc
	os.remove(name + ".old")