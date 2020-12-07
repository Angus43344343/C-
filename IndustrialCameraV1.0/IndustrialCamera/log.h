#ifndef _LOG_H__
#define _LOG_H__

class CLog//使用单例模式：文件资源共享一个操作对象
{
public:
	static CLog *GetInstance() { return ms_pInstanceLog; }
	void SaveLog(PCHAR pcData, ULONG ulDataLen);
	private:
		CLog() {}
		~CLog(){}
		static CLog *ms_pInstanceLog;
		class CReleaseInstance 
		{
		public:
			~CReleaseInstance() { if(nullptr != CLog::ms_pInstanceLog) delete ms_pInstanceLog; }
		};
		static CReleaseInstance ms_RealseInstance;
};

#endif /*_LOG_H__*/