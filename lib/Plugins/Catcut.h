#ifndef CATCUT_H_
#define CATCUT_H_

#include "Plugin.h"
#include "Reporter.h"

class CReporterCatcut : public CReporter
{
    private:
	std::string m_sCatcutURL;
	std::string m_sLogin;
	std::string m_sPassword;
	bool m_bNoSSLVerify;
	int m_nRetryCount;
	int m_nRetryDelay;

    public:
        CReporterCatcut();
        virtual ~CReporterCatcut();

        virtual void SetSettings(const map_plugin_settings_t& pSettings);

        virtual std::string Report(const map_crash_data_t& pCrashData,
                                   const map_plugin_settings_t& pSettings,
                                   const char *Args);
};

#endif /* CATCUT_H_ */
