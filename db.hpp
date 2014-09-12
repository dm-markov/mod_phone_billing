
/**************************************************************************************
 *
 *	���� ������� � ������
 *
 */

#ifdef _DEBUG___
   #define _CRTDBG_MAP_ALLOC
   #include <stdlib.h>
   #include <crtdbg.h>
   #define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#pragma once
#ifndef _DB_HPP_
#define _DB_HPP_
#ifndef RC_INVOKED

#include <exception>

#include <string>

class DB_Dataset;

class DB_Connection {
public:
	virtual ~DB_Connection();
	DB_Connection();
private:
	//! copy-ctor --- ��������, �.�. ���� ��������� ��������
	//! �������������� �������� ��� ����� ���������� ����
	DB_Connection(const DB_Connection&);
	//! assign-oper --- ��������, �� �������� ��������� � copy-ctor
	void operator=(const DB_Connection&);
public:
	//virtual void attach(char const* file, char const* user, char const* pass);
	//virtual void detach();
	virtual void connect(char const* file, char const* user, char const* pass);
	virtual void disconnect();
	virtual DB_Dataset sql_exec(char const* statement);
private:
	void*      		db_handle_;
	std::string		db_name_str_;
	std::string		db_user_str_;

	std::string		file_str_;
	std::string		user_str_;
public:
};

class DB_Handle {
public:
	virtual ~DB_Handle();
	DB_Handle();
private:
	//! copy-ctor --- ��������, �.�. ���� ��������� ��������
	//! �������������� �������� ��� ����� ���������� ����
	//DB_Handle(DB_Handle const&);
	//! assign-oper --- ��������, �� �������� ��������� � copy-ctor
	void operator=(DB_Handle const&);
public:
	virtual void connect(std::string const& file, std::string const& user, std::string const& pass);
	virtual void disconnect();
	virtual DB_Dataset exec_sql(std::string const&);
	void* handle() const { return db_handle_; }
	std::string	const& file_name() const { return file_name_; }
	std::string	const& user_name() const { return user_name_; }
//	operator()
private:
	void*			db_handle_;
	std::string		file_name_;
	std::string		user_name_;
};


class DB_Dataset {
	//! default-ctor --- ��������, �.�. ��� ������ �� DB_Connection
	//! ���-�� � ����� �����, ������ ������ �� ������������ ��������
	DB_Dataset();
	//! copy-ctor --- ��������, �.�. ��������� �������� �����, ���� ���
	//! ����������� ������, �� ����� fetch() � ����� ������� ������� �����������
	//! SQL-������� � � ������� �����, ��� �������� � �������� ��������� �������
	//! ������ �� SQL-������� � ����� �� �������� SQLStatement.
	//! ����������� �������: ����������� SQL-������
//	DB_Dataset(DB_Dataset const&);
	//! assign-oper --- ��������, �� �������� ��������� � copy-ctor
//	DB_Dataset& operator=(DB_Dataset const&);
public:
	virtual ~DB_Dataset();
	DB_Dataset(DB_Handle const& db_conn, std::string const& sql_str);
	//DB_Dataset(DB_Handle const& db_conn, char const* const sql_ptr):DB_Dataset(DB_Handle const& db_conn, std::string const& sql_str);
	virtual bool fetch();
	char const* field(int idx, char const* idx_nil="") const { 
		char const* ptr = 0;
		if( stmt_idxs_ptr_ && idx>=0 && idx<stmt_idxs_num_ ) ptr = stmt_idxs_ptr_[idx];
		return ptr?ptr:idx_nil; 
	}
private:
	//
	//	����������� ������
	//
	DB_Handle const&	    db_conn_;          //!< ���������� � ��
//	int                     sql_code_;         //!< ��� �������� �������
	char**					sql_data_pool_;    //!< ��������� �� ��� ������
	void*               	stmt_handle_;      //!< ������� sql-���������
	void*					stmt_handle_tr_;   //!< ������� sql-����������
	int						stmt_idxs_num_;    //!< ���-�� ����� � �������
	char**					stmt_idxs_ptr_;    //!< ��������� �� ������� �����
	std::string const      	stmt_str_;         //!< sql-��������
/*
	DB_Handle const&	    db_conn_;          //!< ���������� � ��
	void*               	stmt_handle_;      //!< ������� sql-���������
	void*					stmt_handle_tr_;   //!< ������� sql-����������
	int						stmt_idxs_num_;    //!< ���-�� ����� � �������
	char**					stmt_idxs_ptr_;    //!< ��������� �� ������� �����
	char*					stmt_pool_ptr_;    //!< ��������� �� ��� ������
	int                     stmt_status_;      //!< ��� �������� �������
	std::string const      	stmt_str_;         //!< sql-��������
	//size_t					stmt_pool_size_;   //!< ������ ���� ������
	//short* sqlda_is_null_;        //! ������ NULL ��������
	//XSQLDA* sqlda_;
	//int* indexes_;
	//size_t fields_;
*/
};

class DB_Exception : public std::exception {
	//DB_Handle const&  db_conn_;
	//std::string const db_name_str_;
	//std::string const db_user_str_;
	//char const* const err_place_ptr_;
	//char const* const sql_func_ptr_;
	//char const* const sql_msg_ptr_;
	//std::string const sql_stmt_str_;
	std::string what_str_;
public:
	DB_Exception::DB_Exception(std::string const& db_name_str, std::string const& db_user_str, std::string const& sql_stmt_str, char const* const sql_func_psz, char const* const sql_err_psz, char const* const err_place_psz);
	virtual const char* what() const { return what_str_.c_str(); }
	virtual ~DB_Exception() {}
/*
_EXCEPTION_INLINE exception& __CLR_OR_THIS_CALL exception::operator=(const exception& _That)
    {
    if (this != &_That)
        {
        _Tidy();

        if (_That._Mydofree)
            {
            _Copy_str(_That._Mywhat);
            }
        else
            {
            _Mywhat = _That._Mywhat;
            }
        }

    return *this;
    }
*/
};

/*
class Product {
	void const* ptr_;
public:
	virtual ~Product() {
		#ifdef _DEBUG
		{std::string str; ::format(str, ">- %1\r\n", func_name_); ::OutputDebugString(str.c_str());}
		#endif
	}
	Product (const char* const func_name):func_name_(func_name) {
		#ifdef _DEBUG
		{std::string str; ::format(str, "%1 ->\r\n", func_name_); ::OutputDebugString(str.c_str());}
		#endif
	}
	//! ���������� ������ ������������ ������� ��������
	long amt() const { return 0; }
	//! ��������� �� ������ ���������� ������� ������������
	char const* art() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ������������ ������������
	char const* name() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ������������ ���������� ��� ������� ������������
	char const* note() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ������������� ������/����������
	char const* price_id() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ���� ������������ ��� ���
	char const* price_our() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� EndUser ���� ������������
	char const* price_usr() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ������ ���� ������������
	char const* price_usr() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ����, � ������� ��������������� ������ ������������
	char const* slot() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ������������� ������������ ������� ������������
	char const* spec() const { return __FUNCTION__; }
	//! ��������� �� ������ ���������� ������� ��������� ������� ������������
	char const* unit() const { return __FUNCTION__; }
};
*/


#ifdef _DEBUG
#include <windows.h> /* ��� OutputDebugString */
#include "../demay/format.hpp"

class function {
	char const* const func_name_;
public:
	explicit function(const char* const func_name):func_name_(func_name) {
		#ifdef _DEBUG
		{std::string str; ::format(str, "%1 ->\r\n", func_name_); ::OutputDebugString(str.c_str());}
		#endif
	}
	~function() {
		#ifdef _DEBUG
		{std::string str; ::format(str, ">- %1\r\n", func_name_); ::OutputDebugString(str.c_str());}
		#endif
	}
};

#endif


#endif /* RC_INVOKED */
#endif /* _DB_HPP_ */