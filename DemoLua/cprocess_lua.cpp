#include "cprocess_lua.h"
#include <QDebug>
#include <string.h>
#include <iostream>
#include<QMessageBox>
CProcess_LUA::CProcess_LUA(QObject *parent) : QObject(parent)
{
    /* 初始化Lua */
    L = luaL_newstate();

    /* 载入Lua基本库 */
    luaL_openlibs(L);

    lua_register(L, "GetLogFrmPro", RefeshLog);


    m_strLuaPath=QString("process.lua");
    QFileInfo fif(m_strLuaPath.toLatin1().data());
    if(!fif.isFile())
    {
        QFile f(m_strLuaPath.toLatin1().data());
        if(f.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream txt(&f);
            txt<<QString("strlog = \"呵呵呵，好玩!\"")<<endl;

            txt<<QString("function ShowLog(nType)")<<endl;
            txt<<QString("if(nType == 0)")<<endl;
            txt<<QString("then")<<endl;
            txt<<QString("strlog = \"我就我,不一样的烟火\"")<<endl;
            txt<<QString("elseif(nType == 1)")<<endl;
            txt<<QString("then")<<endl;
            txt<<QString("strlog = \"测试\"")<<endl;
            txt<<QString("else")<<endl;
            txt<<QString("end")<<endl;
            txt<<"return strlog,2,3"<<endl;
            txt<<"end"<<endl;

            txt<<QString("function RefeshLog(str)")<<endl;
            txt<<QString("strlog=str")<<endl;
            txt<<QString("GetLogFrmPro(str)")<<endl;
            txt<<QString("end")<<endl;

            txt.flush();
            f.close();
        }
    }

    luaL_dofile(L, m_strLuaPath.toLatin1().data());
}
CProcess_LUA::~CProcess_LUA()
{
    /*cleanup Lua*/
    lua_close(L);
}


QString CProcess_LUA::getLog()
{
    QString strValue = "";
    QString strLog ="";
    qDebug()<<strLog.sprintf("栈大小:%d\n",lua_gettop(L));

    lua_getglobal(L,"ShowLog");   //入栈1函数名
    lua_pushinteger(L,2);//入栈2参数

    qDebug()<<strLog.sprintf("栈大小:%d\n", lua_gettop( L ) );
    lua_pcall(L,1,3,0);          //调用函数，返回3个值入栈

    qDebug()<<strLog.sprintf("栈大小:%d\n", lua_gettop( L ) );
    if(lua_isstring(L,1))
    {
        std::string str = lua_tostring(L,1); //调取栈底元素
        strValue =QString::fromStdString(str);
    }
    lua_pop(L,-1);//清空栈
    qDebug()<<strLog.sprintf("栈大小:%d\n", lua_gettop( L ) );

    return strValue;
}

void  CProcess_LUA::setLog(QString strLog)
{
    QString str ="";
    qDebug()<<str.sprintf("RefeshLog栈大小:%d\n", lua_gettop( L ) );
    lua_getglobal(L,"RefeshLog");
    lua_pushlstring(L,strLog.toStdString().c_str(),strLog.toStdString().length());
    qDebug()<<str.sprintf("RefeshLog栈大小:%d\n", lua_gettop( L ) );
    lua_pcall(L,1,0,0);
    lua_pop(L,-1);//清空栈

}
int CProcess_LUA::RefeshLog(lua_State *L)
{
   std::string str =lua_tostring(L,1);
   QString strValue =QString::fromStdString(str);
   QMessageBox::information(NULL,tr("提示"),strValue);
   return 1;
}
