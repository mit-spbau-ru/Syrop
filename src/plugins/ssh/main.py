import ssh

if __name__ == "__main__" :

	ssh.makeConfigFile();
	#ssh.copyBackupFile("192.168.0.1","1234")
	ssh.cleanupSettings()
