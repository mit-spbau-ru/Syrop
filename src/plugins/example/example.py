def setupSettings (settings):
	if "https" in settings:
		print settings["https"]
	else:
		print settings["http"]

def cleanupSettings ():
	print "cleanned"