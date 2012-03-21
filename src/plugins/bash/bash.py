import os

def setupSettings (settings):
	findProxyParameters()
	writeProxyFile(settings)

def cleanupSettings ():
	os.remove("~/.proxy_settings")

def writeProxyFile (settings):
	file = open("~/.proxy_settings", "w")
	if settings.hasProxy("http"):
		file.write("http_proxy=" + settings.getProxy("http") + "\n")
	if settings.hasProxy("https"):
		file.write("https_proxy=" + settings.getProxy("https") + "\n")
	file.close()

def findProxyParameters ():
	bashrc = open("~/.bashrc", "r")
	for line in bashrc.readlines():
		if line.lower().find("http_proxy") != -1:
			return
		if line.lower().find("proxy_settings") != -1:
			return
	bashrc.close()
	bashrc = open("~/.bashrc", "a")
	bashrc.write("\n\n")
	bashrc.write("if [ -f ~/.proxy_settings ]; then\n")
	bashrc.write("\t. ~/.proxy_settings\n")
	bashrc.write("fi")
	bashrc.close()