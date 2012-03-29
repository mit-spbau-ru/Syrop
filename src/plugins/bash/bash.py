import os

def setupSettings (settings):
	findProxyParameters()
	writeProxyFile(settings)

def cleanupSettings ():
	os.remove(os.path.expanduser("~/.proxy_settings"))

def writeProxyFile (settings):
	file = open(os.path.expanduser("~/.proxy_settings"), "w")
	if "http" in settings:
		file.write("http_proxy=" + settings["http"] + "\n")
		file.write("export http_proxy\n")
	if "https" in settings:
		file.write("https_proxy=" + settings["https"] + "\n")
		file.write("export https_proxy\n")
	file.close()

def findProxyParameters ():
	name = os.path.expanduser("~/.bashrc")
	bashrc = open(name, "r")
	for line in bashrc.readlines():
		if line.lower().find("http_proxy") != -1:
			return
		if line.lower().find("proxy_settings") != -1:
			return
	bashrc.close()
	bashrc = open(name, "a")
	bashrc.write("\n\n")
	bashrc.write("if [ -f ~/.proxy_settings ]; then\n")
	bashrc.write("\t. ~/.proxy_settings\n")
	bashrc.write("fi\n")
	bashrc.close()