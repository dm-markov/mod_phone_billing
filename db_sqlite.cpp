#include "db.hpp"

#include "../demay/format.hpp"
#include "../sqlite-3.6.22/src/sqlite.h.in"

	DB_Exception::DB_Exception(std::string const& db_name_str, std::string const& db_user_str, std::string const& sql_stmt_str, 
		char const* const sql_func_psz, char const* const sql_err_psz, char const* const err_place_psz) {
		::format(what_str_, 
			"DB_Exception->%1:\r\n"
			"   file_name \"%2\"\r\n"
			"   user_name \"%3\"\r\n"
			"   statement \"%4\"\r\n"
			"   error_txt \"%5\"\r\n"
			"   raises_in \"%6\""
			, sql_func_psz, db_name_str, db_user_str, sql_stmt_str, sql_err_psz, err_place_psz
			);
	}

#ifdef __SQLITE_ERRORS__
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR        1   /* SQL error or missing database */
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE_PERM         3   /* Access permission denied */
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
#define SQLITE_BUSY         5   /* The database file is locked */
#define SQLITE_LOCKED       6   /* A table in the database is locked */
#define SQLITE_NOMEM        7   /* A malloc() failed */
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE_NOTFOUND    12   /* NOT USED. Table or record not found */
#define SQLITE_FULL        13   /* Insertion failed because database is full */
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE_PROTOCOL    15   /* NOT USED. Database lock protocol error */
#define SQLITE_EMPTY       16   /* Database is empty */
#define SQLITE_SCHEMA      17   /* The database schema changed */
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE_MISMATCH    20   /* Data type mismatch */
#define SQLITE_MISUSE      21   /* Library used incorrectly */
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE_AUTH        23   /* Authorization denied */
#define SQLITE_FORMAT      24   /* Auxiliary database format error */
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */
/* end-of-error-codes */
#endif


/*
	&ldquo; 	левая кавычка
	&rdquo; 	правая кавычка
	&ndash;		длинное тире
*/

DB_Handle::~DB_Handle() {
}

DB_Handle::DB_Handle() :db_handle_(0), file_name_(), user_name_() {
}


#ifdef _DEBUG
#include <windows.h> /* для OutputDebugString */
#endif

sqlite3* sqlite3_handle_global = 0;

void DB_Handle::connect(std::string const& file, std::string const& user, std::string const& pass) {
	if( 0==this->db_handle_ ) {
		sqlite3* sqlite3_handle = 0;
		int sqlt_code = ::sqlite3_open(
			file.c_str(),                  // Database filename (UTF-8)
			&sqlite3_handle                // OUT: SQLite db handle
		);
		if( sqlt_code ) throw DB_Exception(file, user, "none", "::sqlite3_open", ::sqlite3_errmsg(static_cast<sqlite3*>(sqlite3_handle)), __FUNCTION__);
		::sqlite3_handle_global = sqlite3_handle;
		this->db_handle_ = sqlite3_handle;
		this->file_name_ = file;
		this->user_name_ = pass;
		#ifdef _DEBUG
		{std::string str; ::format(str, "    %1 -> 0x%2, '%3'\r\n", __FUNCTION__, (void*)sqlite3_handle, file); ::OutputDebugString(str.c_str());}
		#endif
	}
#ifdef __UTF16__not_worked_
	int sqlite3_open(
		const char *filename,   /* Database filename (UTF-8) */
		sqlite3 **ppDb          /* OUT: SQLite db handle */
	);
	int sqlite3_open_v2(
		const char *filename,   /* Database filename (UTF-8) */
		sqlite3 **ppDb,         /* OUT: SQLite db handle */
		int flags,              /* Flags */
		const char *zVfs        /* Name of VFS module to use */
	);

	int sqlite3_open16(
		const void *filename,   /* Database filename (UTF-16) */
		sqlite3 **ppDb          /* OUT: SQLite db handle */
	);
#endif
}

void DB_Handle::disconnect() {
	#ifdef _DEBUG
	{std::string str; ::format(str, "    %1 -> 0x%2, '%3'\r\n", __FUNCTION__, (void*)this->db_handle_, file_name_); ::OutputDebugString(str.c_str());}
	#endif
	if( this->db_handle_ ) {
		int sqlt_code = ::sqlite3_close(static_cast<sqlite3*>(this->db_handle_));
		if( sqlt_code ) throw DB_Exception(file_name_, user_name_, "none", "::sqlite3_close", ::sqlite3_errmsg(static_cast<sqlite3*>(db_handle_)), __FUNCTION__);
		this->db_handle_ = 0;
	}
}

/*
sqlite3_open() 	 This routine opens a connection to an SQLite database file and returns a database connection object. This is often the first SQLite API call that an application makes and is a prerequisite for most other SQLite APIs. Many SQLite interfaces require a pointer to the database connection object as their first parameter and can be thought of as methods on the database connection object. This routine is the constructor for the database connection object. 
*/
/*
class DB_Dataset {
	DB_Connection const&	db_conn_;        //!< соединения с БД
	std::string         	sql_str_;        //!< sql-оператор
	void*               	stmt_handle_;    //!< хендлер sql-оператора
	void*					tr_handle_;      //!< хендлер транзакции
	char*					sqldata_ptr_;    //!< указатель на пул данных
	size_t					sqldata_size_;  //!< размер пула данных
*/
DB_Dataset::DB_Dataset(DB_Handle const& db_conn, std::string const& sql_str)
	:db_conn_(db_conn), sql_data_pool_(0), stmt_handle_(0), stmt_handle_tr_(0), stmt_idxs_num_(0), stmt_idxs_ptr_(0), stmt_str_(sql_str) {
	#ifdef __NOT__
	int sqlite3_prepare_v2(
			sqlite3 *db,            // Database handle
			const char *zSql,       // SQL statement, UTF-8 encoded
			int nByte,              // Maximum length of zSql in bytes.
			sqlite3_stmt **ppStmt,  // OUT: Statement handle
			const char **pzTail     // OUT: Pointer to unused portion of zSql
			);
	//#endif
	stmt_status_ = ::sqlite3_prepare_v2(
			static_cast<sqlite3*>(db_conn_.handle()),   // Database handle
			stmt_str_.c_str(),                          // SQL statement, UTF-8 encoded
			stmt_str_.length(),                         // Maximum length of zSql in bytes.
			(sqlite3_stmt**)&stmt_handle_,              // OUT: Statement handle
			0                                           // OUT: Pointer to unused portion of zSql
			);
	#endif
	sqlite3_stmt* stmt_handle(0);
	int sqlt_code = ::sqlite3_prepare_v2(
			static_cast<sqlite3*>(db_conn_.handle()),   // Database handle
			stmt_str_.c_str(),                          // SQL statement, UTF-8 encoded
			stmt_str_.length(),                         // Maximum length of zSql in bytes.
			&stmt_handle,                               // OUT: Statement handle
			0                                           // OUT: Pointer to unused portion of zSql
			);
	if( sqlt_code ) throw DB_Exception(db_conn_.file_name(), db_conn_.user_name(), stmt_str_.c_str(), "::sqlite3_prepare_v2", ::sqlite3_errmsg(static_cast<sqlite3*>(db_conn_.handle())), __FUNCTION__);
	this->stmt_handle_ = stmt_handle;
	#ifdef _DEBUG 
	{std::string deb_str; ::format(deb_str, "%1 [0x%2]\n", stmt_str_, stmt_handle_); ::OutputDebugString(deb_str.c_str());}
	#endif
}

#ifdef ____NOT__
DB_Handle::DB_Handle(DB_Handle const& db_conn)
	:db_conn_(db_conn), stmt_handle_(0), stmt_handle_tr_(0), stmt_idxs_ptr_(0), stmt_pool_ptr_(0), stmt_status_(0), stmt_str_(sql_str){
		/*
	db_conn_;          //!< соединения с БД
	void*               	stmt_handle_;      //!< хендлер sql-оператора
	void*					stmt_handle_tr_;   //!< хендлер sql-транзакции
	int						stmt_idxs_num_;    //!< кол-во полей в запросе
	char**					stmt_idxs_ptr_;    //!< указатель на индексы полей
	char*					stmt_pool_ptr_;    //!< указатель на пул данных
	int                     stmt_status_;      //!< код возврата функций
	std::string const      	stmt_str_;         //!< sql-оператор
	*/
}
#endif

bool DB_Dataset::fetch() {
	//
	// здесь проверять статус установленный в конструкторе
	//
	int sqlt_code = ::sqlite3_step(static_cast<sqlite3_stmt*>(stmt_handle_));
	#ifdef _DEBUG 
	{std::string deb_str; ::format(deb_str, "\t\tsqlt_code = %1 [0x%2]\n", sqlt_code, stmt_handle_); ::OutputDebugString(deb_str.c_str());}
	#endif
	if( 100==sqlt_code ) {
///todo:				if( stmt_idxs_ptr_ ) delete stmt_idxs_ptr_;
///todo:		if( stmt_pool_ptr_ ) delete stmt_pool_ptr_;
		int all_column_bytes = 0;
		stmt_idxs_num_ = 0; //!< поля (колонки), возвращаемые sql-оператором нумеруются с 0
		while( int column_bytes=::sqlite3_column_bytes(static_cast<sqlite3_stmt*>(stmt_handle_), stmt_idxs_num_) ) {
			all_column_bytes += column_bytes; //!< плюсуем все размеры (длины) возвращаемых полей 
			all_column_bytes++; //!< для концевого NULL каждого поля 
			//#ifdef _DEBUG
			//{std::string deb_out; ::format(deb_out, __FUNCTION__" column-> bytes=%1, text=\'%2\'\r\n", column_bytes, (char*)::sqlite3_column_text(static_cast<sqlite3_stmt*>(stmt_handle_), stmt_idxs_num_)); ::OutputDebugString(deb_out.c_str());}
			//#endif
			stmt_idxs_num_++;
		}
		//! в итоге здесь stmt_idxs_num_ равен кол-ву полей например 5, доступ к которым от 0...4
		//#ifdef _DEBUG
		//{std::string deb_out; ::format(deb_out, __FUNCTION__" total-> stmt_idxs_num_=%1, all_column_bytes=%2\r\n", stmt_idxs_num_, all_column_bytes); ::OutputDebugString(deb_out.c_str());}
		//#endif
		stmt_idxs_ptr_ = new char* [stmt_idxs_num_];
///todo:		stmt_pool_ptr_ = new char [all_column_bytes];
		for( int i=0; i<stmt_idxs_num_; i++ ) {
///todo:			int bytes = ::sqlite3_column_bytes(static_cast<sqlite3_stmt*>(stmt_handle_), i);
			char* ptr = (char*)::sqlite3_column_text(static_cast<sqlite3_stmt*>(stmt_handle_), i);
			stmt_idxs_ptr_[i] = ptr;
			//#ifdef _DEBUG
			//{std::string deb_out; ::format(deb_out, __FUNCTION__" stmt_idxs_ptr[%1] = 0x%2\r\n", i, (void*)ptr); ::OutputDebugString(deb_out.c_str());}
			//#endif
		};
		return true;
	}

	return false;
}

DB_Dataset::~DB_Dataset() {
	try { //__try {
	int sql_code = ::sqlite3_finalize(static_cast<sqlite3_stmt*>(stmt_handle_));
	} catch(...) { //} __finally {
		// при возникновении SEH-исключений из '::sqlite3_finalize' ничего не делаем
	}
}

DB_Dataset DB_Handle::exec_sql(std::string const& sql_stmt_str) {
	return DB_Dataset(*this, sql_stmt_str);
}
