import os

def setupSettings (settings):
	if "http" in settings:
		lst = splitProxy(settings["http"])
		makeBackupFile()
		copyBackupFile(lst[0], lst[1])

def cleanupSettings ():
	name = os.path.expanduser("~/.subversion/servers")
	if os.path.exists(name + ".old"):
		os.rename(name + ".old", name)

def makeBackupFile ():
	name = os.path.expanduser("~/.subversion/servers")
	if not os.path.exists(name):
		cfg = opend(name, "w")
		cfg.close()

def splitProxy (proxy):
	return proxy.split(':')

def copyBackupFile (server, port):
	name = os.path.expanduser("~/.subversion/servers")
	os.rename(name, name + ".old")
	config = open(name + ".old", "r")
	outconf = open(name, "w")
	for line in config.readlines():
		newline = line.strip();
		if newline == "[global]":
			outconf.write(newline + "\n")
			outconf.write("http-proxy-host = " + server + "\n")
			outconf.write("http-proxy-port = " + port + "\n")
		elif (newline != "") and (newline[0] != '#') and (newline.find("http-proxy-host") == -1) and (newline.find("http-proxy-port") == -1):
			outconf.write(newline + "\n")
	outconf.close()
	config.close()
