#!/usr/bin/env python
# -*- coding: utf-8 -*-
import ConfigParser, os, re
from subprocess import Popen
from subprocess import PIPE

def backupSettings ():
	pass

###
### @param settings - dictionary of settings
### @param s - type of protocol
###
def setupSettings (settings, s) :
	#проверяем что есть нужные настройки
    t = s.strip()
    if t in settings :
        params = splitProxyString(settings[t])
        
        if 'server' in params :
            olduse = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/use_"+t+"_proxy"], stdout=PIPE ).communicate()[0]
            ret = subprocess.call ( "gconftool -s /system/"+t+"proxy/old_use_"+t+"_proxy -t bool " + str(olduse), shell = True )                
            ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/use_"+t+"_proxy -t bool true ", shell = True )                
            
            if olduse :
                print olduse
                oldhost = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/host"], stdout=PIPE ).communicate()[0] 
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_host -t int " + oldhost, shell = True ) 
                    
            ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/host -t int " + params['server'], shell = True ) 

        if 'port' in params :
            if olduse :
                oldport = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/port"], stdout=PIPE ).communicate()[0] 
                print oldport
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_port -t int " + oldport, shell = True ) 

            ret = subprocess.call( "gconftool -s /system/"+t+"_proxy/port -t int " + params['port'], shell = True ) 

        
        if 'user' in params:
            if olduse :
                olduser = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/authentification_user"], stdout=PIPE ).communicate()[0] 
                print olduser
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_user -t string " + olduser, shell = True ) 

            ret = subprocess.call( "gconftool -s /system/"+t+"_proxy/authentification_user -t string " + params['user'], shell = True )
        
        if 'password' in params:
            if olduse :
                oldpwd = Popen ( ["gconftool", "-g", "/system/"+t+"_proxy/authentification_password"], stdout=PIPE ).communicate()[0] 
                print oldpwd
                ret = subprocess.call ( "gconftool -s /system/"+t+"_proxy/old_pwd -t string " + oldpwd, shell = True ) 

            ret = subprocess.call( "gconftool -s /system/"+t+"_proxy/authentification_password -t string " + params['password'], shell = True )
  	

def cleanupSettings ():

    for s in { 'http', 'ftp' } :
        olduse = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_use_"+s+"_proxy"], stdout=PIPE ).communicate()[0] 
        if (olduse) :
        
            subprocess.call( "gconftool -s /system/"+s+"_proxy/use_"+s+"_proxy " + olduse, shell = True ) 
            
            oldhost = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_host"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/host -t int " + str(oldhost), shell = True )        

            oldport = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_port"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/port -t int " + str(oldport), shell = True ) 

        
            olduser = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_user"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/authentification_user -t string " + str(olduser), shell = True ) 

                
            oldpwd = Popen ( ["gconftool", "-g", "/system/"+s+"_proxy/old_pwd"], stdout=PIPE ).communicate()[0] 
            ret = subprocess.call ( "gconftool -s /system/"+s+"_proxy/authentification_password -t string " + str(oldpwd), shell = True ) 

  	      
def sectionString (string):
	m = re.match(r"^\[\s*(.+)\s*\]$", string.strip(None))
	if m is not None:
		return m.group(1)
	return None

#функция ожидает строку вида [user:password@]server[:port]
def splitProxyString (conf):
	params = {}
	m = re.match(r"^(([^:@]+)[:]([^:@]+)[@]){,1}([^:@]+){1}[:]([^:@]+){,1}$", conf.strip(None))

	if m is not None:
		if m.group(2) is not None:
			params['user'] = m.group(2)
		if m.group(3) is not None:
			params['password'] = m.group(3)
		if m.group(4) is not None:
			params['server'] = m.group(4)
		if m.group(5) is not None:
			params['port'] = m.group(5)

	return params

#
# usage example :
#
#conf = {'http' : "us:pas@12.12.12.12:1"}
#setupSettings(conf,"http")
#cleanupSettings()
