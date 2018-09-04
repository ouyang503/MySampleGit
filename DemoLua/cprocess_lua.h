#ifndef CPROCESS_LUA_H
#define CPROCESS_LUA_H

#include <QObject>
#include<QtCore>
extern "C"
{
#include <lua.h>
#include <luaconf.h>
#include <lualib.h>
#include <lauxlib.h>
}

class CProcess_LUA : public QObject
{
    Q_OBJECT
public:
    explicit CProcess_LUA(QObject *parent = 0);
    ~CProcess_LUA();
    QString getLog();
    void  setLog(QString strLog);

    static int RefeshLog(lua_State *L);
private:
    lua_State* L;
    QString m_strLuaPath;
signals:

public slots:
};

#endif // CPROCESS_LUA_H
