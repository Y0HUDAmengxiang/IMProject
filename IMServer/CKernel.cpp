#include "CKernel.h"
#include "TcpNetServerMediator.h"
#include "config.h"
//静态成员变量在类外初始化
CKernel* CKernel::pKernel = nullptr;
CKernel::CKernel() {
	
	pKernel = this;
	m_pMediator = new TcpNetServerMediator;
	pKernel->setFunMap();
}
CKernel::~CKernel() {

}

//打开服务器
bool CKernel::startServer() {
	//打开网络
	if (!m_pMediator->OpenNet()) {
		cout << "open tcp server fail" << endl;
		return false;
	}
	//连接数据库

	if (!m_Sql.ConnectMySql("127.0.0.1","root","2308221223","im_sql")) {
		cout << "connect mysql fail" << endl;
		return false;
	}
	else {
		cout << "connect mysql sucess" << endl;
	}
	return true;

}
//关闭服务器
void CKernel::CloseServer() {

	//回收资源
	if (m_pMediator) {
		m_pMediator->CloseNet();
		delete m_pMediator;
		m_pMediator = nullptr;
	}
	//断开和数据库的连接
	m_Sql.DisConnect();
}
//初始化函数指针
void CKernel::setFunMap() {
	cout << "CKernel::setFunMap" << endl;
	memset(m_funMap, 0, sizeof(m_funMap));
	m_funMap[_DEF_TCP_REGISTER_RQ - _DEF_PROTOCOL_BASE - 1] = &CKernel::dealRegisterRq;
	m_funMap[_DEF_TCP_LOGIN_RQ - _DEF_PROTOCOL_BASE - 1] = &CKernel::dealLoginRq;
	m_funMap[_DEF_TCP_CHAT_RQ - _DEF_PROTOCOL_BASE - 1] = &CKernel::dealChatRq;
	m_funMap[_DEF_TCP_OFFLINE_RQ - _DEF_PROTOCOL_BASE - 1] = &CKernel::dealOfflineRq;
	m_funMap[_DEF_TCP_ADD_FRIEND_RQ - _DEF_PROTOCOL_BASE - 1] = &CKernel::dealAddFriendRq;
	m_funMap[_DEF_TCP_ADD_FRIEND_RS - _DEF_PROTOCOL_BASE - 1] = &CKernel::dealAddFriendRs;    
}
//调用协议头处理函数
void CKernel::ReadyData(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::ReadyData ; " << recvBuf << endl;
	PackType type = *(PackType*)recvBuf;
	//根据协议头走到对应的处理函数
	//计算数组下表
	int index = type - _DEF_PROTOCOL_BASE - 1;
	if (index > 0 && index <= _DEF_PROTOCOL_CONT) {
		PFUN pf = m_funMap[index];
		if (pf) {
			(this->*pf)(lSend, recvBuf, nLen);
		}
		else
		{
			cout << "type: " << type << endl;
		}
	}
	else
	{
		cout << "type: " << type << endl;
		
	}
	delete[] recvBuf;
	
}
//处理注册请求
void CKernel::dealRegisterRq(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::dealRegisterRq" << endl;
	//1.拆包
	_STRU_TCP_REGISTER_RQ* rq = (_STRU_TCP_REGISTER_RQ*)recvBuf;
	//2.校验数据合法性

	//3.根据电话从数据库中查询
	list<string> resList;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select tel from usertable where tel = '%s';", rq->tel);
	if (!m_Sql.SelectMySql(sqlBuf, 1, resList)) {
		cout << "查询数据库失败：" << sqlBuf << endl;
		return;
	}
	_STRU_TCP_REGISTER_RS rs;
	//4.遍历查询结果
	if (resList.size() > 0) {
		//查询到，说明电话号码被注册过，就注册失败
		rs.result = tel_is_used;
	}
	else
	{
		//根据昵称从数据库中查询
		sprintf(sqlBuf, "select tel from usertable where userName = '%s';", rq->name);
		if (!m_Sql.SelectMySql(sqlBuf, 1, resList)) {
			cout << "查询数据库失败：" << sqlBuf << endl;
			return;
		}
		//6.遍历查询结果
		if(resList.size()>0)
		{
			//查询到，说明昵称被注册过，就注册失败
			rs.result = name_is_exists;
		}
		else
		{
			//7.把用户写入数据库
			sprintf(sqlBuf, "insert into usertable (userName,tel,pass,xiabibi,iconid) values ('%s','%s','%s','爷是程序带师',1);", rq->name, rq->tel, rq->password);
			if (!m_Sql.UpdateMySql(sqlBuf)) {
				cout << "更新数据库失败：" << sqlBuf << endl;
				return;
			}
			//8.注册成功
			rs.result = register_success;

		}
		
		
	}
	m_pMediator->SendData(lSend, (char*)&rs, sizeof(rs));

}
//处理登录请求
void CKernel::dealLoginRq(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::dealLoginRq" << endl;
	//1.拆包
	_STRU_TCP_LOGIN_RQ* rq = (_STRU_TCP_LOGIN_RQ*)recvBuf;
	//2.校验参数合法性

	//3.从数据库根据电话号码查询密码
	list<string> resList;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select id,pass from usertable where tel = '%s';", rq->tel);
	if (!m_Sql.SelectMySql(sqlBuf, 2, resList)) {
		cout << "查询数据库失败" << endl;
		return;
	}
	_STRU_TCP_LOGIN_RS rs;
	//遍历查询结果
	if (0 == resList.size()) {
		//没查到，说明登陆失败，电话号没有注册
		rs.result = user_not_exists;

	}
	else
	{
		//取出id
		int userId = stoi(resList.front());
		resList.pop_front();
		//取出数据库里的密码
		string password = resList.front();
		resList.pop_front();
		//5.比较数据库的密码和输入的密码是否一致
		if (0 == strcmp(rq->password, password.c_str())) {
			//相等说明登录成功
			rs.result = login_success;
			rs.id = userId;
			m_pMediator->SendData(lSend, (char*)&rs, sizeof(rs));
			//保存用户id和对应的SOCKET
			m_mapidToSocket[userId] = lSend;
			//获取好友信息列表
			getFriendInfoList(userId);

		}
		else
		{
			rs.result = password_error;
		}
	}
	m_pMediator->SendData(lSend, (char*)&rs, sizeof(rs));
}
//查询好友信息
void CKernel::getFriendInfoList(int userId) {
	cout << "CKernel::getFriendInfoList" << endl;

	//根据自己id查询自己的信息
	_STRU_TCP_FRIEND_INFO_RQ userInfo;
	getUserInfoById(userId, &userInfo);
	//把自己信息发给客户端
	m_pMediator->SendData(m_mapidToSocket[userId], (char*)&userInfo, sizeof(userInfo));
	//根据自己的id查询好友id
	list<string> resList;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select idB from t_friend where idA = '%d';", userId);
	if (!m_Sql.SelectMySql(sqlBuf, 1, resList)) {
		cout << "查询数据库失败" << endl;
		return;
	}
	int friendId = 0;
	_STRU_TCP_FRIEND_INFO_RQ friendInfo;
	while (resList.size()>0) {
		//遍历好友id列表
		friendId = stoi(resList.front());
		resList.pop_front();
		//根据好友id查询好友信息
		getUserInfoById(friendId, &friendInfo);
		//把好友信息发给客户端
		m_pMediator->SendData(m_mapidToSocket[userId], (char*)&friendInfo, sizeof(friendInfo));
		//给在线好友转发自己的信息
		if (m_mapidToSocket.count(friendId) > 0) {
			m_pMediator->SendData(m_mapidToSocket[friendId], (char*)&userInfo, sizeof(userInfo));
		}
	}
}
//通过id查询好友信息
void CKernel::getUserInfoById(int id, _STRU_TCP_FRIEND_INFO_RQ* info) {
	cout << "CKernel::getUserInfoById" << endl;
	info->id = id;
	if (m_mapidToSocket.count(id) > 0) {
		info->status = status_online;
	}
	else
	{
		info->status = status_offline;
	}
	//根据id查签名和头像
	list<string> resList;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select userName,xiabibi,iconid from usertable where id = '%d';", id);
	if (!m_Sql.SelectMySql(sqlBuf, 3, resList)) {
		cout << "查询数据库失败" << endl;
		return;
	}

	if (3 == resList.size()) {
		strcpy(info->friendName, resList.front().c_str());
		resList.pop_front();
		strcpy(info->feeling, resList.front().c_str());
		resList.pop_front();

		info->iconId = stoi(resList.front());
		resList.pop_front();
	}
}
//处理聊天请求
void CKernel::dealChatRq(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::dealChatRq" << endl;
	//1.拆包
	_STRU_TCP_CHAT_RQ* rq = (_STRU_TCP_CHAT_RQ*)recvBuf;
	//2.查看好友是否在线
	if (m_mapidToSocket.count(rq->friendId) >0) {
		
		/*
		* rq不用取地址，rq已经是指针了
		*/
		m_pMediator->SendData(m_mapidToSocket[rq->friendId], recvBuf, nLen);
		/*第二种写法*/
		/*
		* m_pMediator->SendData(m_mapidToSocket[rq->friendId], recvBuf, nLen);
		* 注意nLen不能写成sizeof（recvBuf）因为recvBuf是一个指针
		* ，sizeof球的是指针的地址，nLen求的才是一个内存长度的地址
		*/
		//m_pMediator->SendData(m_mapidToSocket[rq->friendId], (char*)rq, sizeof(rq));
		
	}
	else
	{
		//如果好友在不在线，转发聊天请求
		_STRU_TCP_CHAT_RS rs;
		rs.result = send_fail;
		rs.friendId = rq->friendId;
		cout << " frirendId:" << rs.friendId << endl;
		m_pMediator->SendData(lSend, (char*)&rs, sizeof(rs));
	}
	
}
//处理下线请求 void CKernel::dealOfflineRq(long lSendIp, char* buf, int nLen)
void CKernel::dealOfflineRq(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::dealOfflineRq" << endl;
	//1.拆包
	_STRU_TCP_OFFLINE_RQ* rq = (_STRU_TCP_OFFLINE_RQ*)recvBuf;

	//根据自己id查询自己的好友id列表
	char sqlBuf[1024] = "";
	list<string>resList;
	sprintf(sqlBuf, "select idB from t_friend where idA = '%d'", rq->userId);
	if (!m_Sql.SelectMySql(sqlBuf, 1, resList)) {
		cout << "数据库查询失败" << endl;
		return;
	}
	
	//遍历好友列表
	int friendId = 0;
	while (resList.size()) {
		//取出好友id
		friendId = stoi(resList.front());
		resList.pop_front();
		//判断好友是否在线

		if (m_mapidToSocket.count(friendId) > 0) {
			//如果好友在线，转发下线请求给好友
			m_pMediator->SendData(m_mapidToSocket[friendId], recvBuf, nLen);
		}
	}

	//把自己id的socket关闭，并且从map中移除节点
	//先判断有没有
	if (m_mapidToSocket.count(rq->userId)>0)
	{
		closesocket(m_mapidToSocket[rq->userId]);
		m_mapidToSocket.erase(rq->userId);

	}
}
//处理添加好友请求
void CKernel::dealAddFriendRq(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::dealAddFriendRq" << endl;
	//1.拆包
	_STRU_TCP_ADD_FRIENDP_RQ* rq = (_STRU_TCP_ADD_FRIENDP_RQ*)recvBuf;
	//2.根据好友的昵称查询好友的id
	char sqlBuf[1024] = "";
	list<string>resList;
	int friendId = 0;
	sprintf(sqlBuf, "select id from usertable where userName = '%s';", rq->friendName);
	if (!m_Sql.SelectMySql(sqlBuf, 1, resList))
	{
		cout << "查询数据库失败，sql：" << sqlBuf << endl;
		return;
	}
	//3.判断查询结果
	//查询结果为空证明好友不存在
	_STRU_TCP_ADD_FRIENDP_RS rs;
	if (0 == resList.size()) {
		//添加好友失败，写添加好友回复，add——friend——ecists
		//好友不存在
		
		rs.result = friend_not_exists;
		rs.friendId = friendId;
		strcpy_s(rs.friendName, rq->friendName);
		rs.userId = rq->userId;
		m_pMediator->SendData(lSend, (char*)&rs, sizeof(rs));
	}
	else
	{
		//取出好友的id
		friendId = stoi(resList.front());
		resList.pop_front();
		//3.判断好友是否在线
		if (m_mapidToSocket.count(friendId) > 0) {
			//如果好友在线，请求转发给好友
			m_pMediator->SendData(m_mapidToSocket[friendId], recvBuf, nLen);
		}
		else
		{
			//如果好友不在线，写田间好友回复，add_friend_offline;
			_STRU_TCP_ADD_FRIEND_RS rs;
			rs.result = friend_offline;
			rs.friendId = friendId;
			strcpy_s(rs.friendName, rq->friendName);
			rs.userId = rq->userId;
			m_pMediator->SendData(lSend, (char*)&rs, sizeof(rs));

		}
	}	
}
//处理添加好友回复
void CKernel::dealAddFriendRs(long lSend, char* recvBuf, int nLen) {
	cout << "CKernel::dealAddFriendRs" << endl;
	//1.拆包
	_STRU_TCP_ADD_FRIENDP_RS* rq = (_STRU_TCP_ADD_FRIENDP_RS*)recvBuf;

	//2.判断对端是否同意添加好友
	if (add_success == rq->result) {
		//3.如果同意把好友关系写入数据库
		char sqlBuf[1024] = "";
		list<string>resList;
		int friendId = 0;
		sprintf(sqlBuf, "insert into t_friend values (%d,%d);", rq->userId,rq->friendId);
		if (!m_Sql.UpdateMySql(sqlBuf))
		{
			cout << "查询数据库失败，sql：" << sqlBuf << endl;
			return;
		}
		sprintf(sqlBuf, "insert into t_friend values (%d,%d);", rq->friendId, rq->userId);
		if (!m_Sql.UpdateMySql(sqlBuf))
		{
			cout << "查询数据库失败，sql：" << sqlBuf << endl;
			return;
		}
		//4.更新客户端好友列表
		getFriendInfoList(rq->userId);
	}
	//4.转发给客户端A
	m_pMediator->SendData(m_mapidToSocket[rq->userId], recvBuf, nLen);
}