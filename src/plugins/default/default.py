def backupSettings ():
	print "backup"

def setupSettings (settings):
	if "http" in settings:
		print settings["http"]
	if "https" in settings:
		print settings["https"]
	if "ftp" in settings:
		print settings["ftp"]
	if "socks" in settings:
		print settings["socks"]

def cleanupSettings ():
	print "cleanned"
