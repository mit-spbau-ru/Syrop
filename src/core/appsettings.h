#ifndef _APP_PROXY_SETTINGS_
#define _APP_PROXY_SETTINGS_

namespace core
{
	//dummy class
	class AppProxySettings
	{
		public:
			std::string getProxy(std::string const &protocol) const
			{
				return "192.168.0.1:3128";
			}
	};

}

#endif //_APP_PROXY_SETTINGS_