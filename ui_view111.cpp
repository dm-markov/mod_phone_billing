#include "ui.hpp"

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"

#ifdef _DEBUG
#include "../demay/file.hpp"
#endif


//todo: раскрутка стека stack unwinding
//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_1(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_2(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_3(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_4(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_5(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_6(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_7(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_8(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}

//! выдать печатную форму "Заявки на ФР" и сохранить заявку в БД
void UI_View111::ev_9(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	ev_plus(html_output, http_args, db_handle);
}


//
//!\brief	Сформировать редактируемую (пользователем) html-форму "Заявка на ФР"
//
//!\note	ДЛЯ КОРРЕКТНОЙ РАБОТЫ: в http_args должны быть переменные "pers" и "bran"
//
void UI_View111::ev_plus(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	if( http_args("pers").empty() ) throw std::exception(__FUNCTION__": Wrong incoming http-args, 'pers' expected");
	if( http_args("bran").empty() ) throw std::exception(__FUNCTION__": Wrong incoming http-args, 'bran' expected");
	#ifdef _DEBUG
	function func("    "__FUNCTION__);
	#endif


//TODO: здесь не формирует  offi

	//
	// ИЗВЛЕКАЕМ_ДАННЫЕ_ИЗ_БД:
	// зная "bran" (Энский) и "pers" (Logon-имя)
	//
	std::string sql_select_fileacc_str;
	::format(sql_select_fileacc_str, 
			"select FILACC_BRANCH_PREF, FILACC_USER_LOGON, FILACC_USER_NAME, FILACC_USER_POST" // [0]-[3]
			", FILACC_KREDIT, FILACC_OPER, FILACC_SCAN, FILACC_KASSA, FILACC_FOTO" // [4]-[8]
			", FILACC_UPRAV, FILACC_GLAVBUH, FILACC_OFFICE, FILACC_SECURITY" // [9]-[12]
			" from FILE_ACCESS where FILACC_BRANCH_PREF='%1' and FILACC_USER_LOGON='%2'"
			, http_args("bran"), http_args("pers")
			);
	DB_Dataset db_dataset_fileacc( db_handle.exec_sql(sql_select_fileacc_str) );
	if( db_dataset_fileacc.fetch() ) {
		std::string sql_select_branch_str;
		::format(sql_select_branch_str, 
				"select BRANCH_PREF, BRANCH_TYPE, BRANCH_NAME from BRANCHES, BRANCH_OWNERS where BRAOWN_BRANCH_PREF=BRANCH_PREF and BRAOWN_USER_LOGON='%1'"
				, http_args("user")
				);
		std::string branch_name_str("ДО \"Эмбургский\"");
		DB_Dataset db_dataset_branch = db_handle.exec_sql(sql_select_branch_str);
		if( db_dataset_branch.fetch() ) {
			branch_name_str.clear();
			::format(branch_name_str, 
					"%2 \"%3\""
					, db_dataset_branch.field(0) // BRANCH_PREF
					, db_dataset_branch.field(1) // BRANCH_TYPE
					, db_dataset_branch.field(2) // BRANCH_NAME
					);
		}
		int next_view = 111;

		::format(html_output,
				#ifdef _DEBUG
				"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
				#endif
				"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
				"\t\t<input type=\"hidden\" name=\"auth\" value=\"%1\">\r\n"
				"\t\t<input type=\"hidden\" name=\"view\" value=\"%2\">\r\n"
				"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
				"\t\t<input type=\"hidden\" name=\"bran\" value=\"%4\">\r\n"
				"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"Назад\">\r\n"
				"\t\t<b><u>Заявка</u></b>\r\n"
				"\t\t<p><font size=\"+1\">На предоставление/изменение прав доступа<br/>к файловым ресурсам офиса ОАО &ldquo;СКБ-банк&rdquo;</font></p>\r\n"
				"\t\t<table cellspacing=\"0\" cellpadding=\"1\"><tr>\r\n"
				"\t\t\t<td>Сотрудник:</td>\r\n"
				"\t\t\t<td><textarea name=\"name\" cols=\"34\" rows=\"1\" wrap=\"soft\">%6</textarea>&nbsp;<textarea name=\"pers\" cols=\"27\" rows=\"1\" wrap=\"soft\">%5</textarea></td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td>&nbsp;</td>\r\n"
				"\t\t\t<td valign=\"top\"><font size=\"-2\">(ФИО, электронный адрес)</font></td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td>Должность:</td>\r\n"
				"\t\t\t<td><textarea name=\"post\" cols=\"64\" rows=\"1\" wrap=\"soft\">%7</textarea></td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td>&nbsp;</td>\r\n"
				"\t\t\t<td valign=\"top\"><font size=\"-2\">(должность сотрудника)</font></td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td>Подразделение:</td>\r\n"
				"\t\t\t<td><textarea name=\"offi\" cols=\"64\" rows=\"1\" wrap=\"soft\" disabled>%8</textarea></td>\r\n" 
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td>&nbsp;</td>\r\n"
				"\t\t\t<td valign=\"top\"><font size=\"-2\">(наименование структурного подразделения)</font></td>\r\n"
				"\t\t</tr></table>\r\n"
				, http_args("auth")
				, next_view
				, http_args("user")
				, db_dataset_fileacc.field(0) // FILACC_BRANCH_PREF
				, db_dataset_fileacc.field(1) // FILACC_USER_LOGON
				, db_dataset_fileacc.field(2) // FILACC_USER_NAME
				, db_dataset_fileacc.field(3) // FILACC_USER_POST
				, branch_name_str
				);

		char const* kredit = db_dataset_fileacc.field(4);
		char const* oper = db_dataset_fileacc.field(5);
		char const* scan = db_dataset_fileacc.field(6);
		char const* kassa = db_dataset_fileacc.field(7);
		char const* foto = db_dataset_fileacc.field(8);
		char const* uprav = db_dataset_fileacc.field(9);
		char const* glavbuh = db_dataset_fileacc.field(10);
		char const* office = db_dataset_fileacc.field(11);
		char const* camera = "";//db_dataset_fileacc.field(12);
		char const* security = db_dataset_fileacc.field(12);
		char const* const on = " checked";
		char const* const off = "";

		::format(html_output,
				"\t\t<p><b><i>Категория доступа к документам:</i></b></p>\r\n"
				"\t\t<table cellspacing=\"0\" cellpadding=\"1\"><tr>\r\n"
				"\t\t\t<th>Доступ<br/><font size=\"-2\">Чтение&nbsp;Запись</font></th><th>Каталог</th><th>Назначение</th>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"kredit_r\"%1/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"kredit_w\"%2/></td>\r\n"
				"\t\t\t<td><b>Kredit</b></td>\r\n"
				"\t\t\t<td>Обмен информацией специалистов кредитного сектора</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"oper_r\"%3/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"oper_w\"%4/></td>\r\n"
				"\t\t\t<td><b>Oper</b></td>\r\n"
				"\t\t\t<td>Обмен информацией специалистов операционного сектора</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"scan_r\"%5/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"scan_w\"%6/></td>\r\n"
				"\t\t\t<td><b>Scan</b></td>\r\n"
				"\t\t\t<td>Скан-копии документов для отправки, с разбиением на подкаталоги в формате YYYY-MM-DD</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"kassa_r\"%7/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"kassa_w\"%8/></td>\r\n"
				"\t\t\t<td><b>Kassa</b></td>\r\n"
				"\t\t\t<td>Обмен информацией специалистов кассового узла</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				, 'R'==*kredit?on:off, 'W'==*kredit?on:off
				, 'R'==*oper?on:off,   'W'==*oper?on:off
				, 'R'==*scan?on:off,   'W'==*scan?on:off
				, 'R'==*kassa?on:off,  'W'==*kassa?on:off
				);
		::format(html_output,
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"foto_r\"%1/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"foto_w\"%2/></td>\r\n"
				"\t\t\t<td><b>Foto</b></td>\r\n"
				"\t\t\t<td>Каталог с фото банкоматов, мероприятий в банке, и т.д.</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"uprav_r\"%3/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"uprav_w\"%4/></td>\r\n"
				"\t\t\t<td><b>Uprav</b></td>\r\n"
				"\t\t\t<td>Документы руководства офиса</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"glavbuh_r\"%5/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"glavbuh_w\"%6/></td>\r\n"
				"\t\t\t<td><b>Glavbuh</b></td>\r\n"
				"\t\t\t<td>Документы главного бухгалтера</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"office_r\"%7/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"office_w\"%8/></td>\r\n"
				"\t\t\t<td><b>Office</b></td>\r\n"
				"\t\t\t<td>Документы общего назначения</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				, 'R'==*foto?on:off,    'W'==*foto?on:off
				, 'R'==*uprav?on:off,   'W'==*uprav?on:off
				, 'R'==*glavbuh?on:off, 'W'==*glavbuh?on:off
				, 'R'==*office?on:off,  'W'==*office?on:off
				);
		::format(html_output,
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"camera_r\"%1/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"camera_w\"%2/></td>\r\n"
				"\t\t\t<td><b>Camera$</b></td>\r\n"
				"\t\t\t<td>Ресурс для размещения фотографий клиентов при оформлении кредитов</td>\r\n"
				"\t\t\t</tr><tr>\r\n"
				"\t\t\t<td align=\"center\"><input type=\"checkbox\" name=\"security_r\"%3/>&nbsp;&nbsp;&nbsp;<input type=\"checkbox\" name=\"security_w\"%4/></td>\r\n"
				"\t\t\t<td><b>Security</b></td>\r\n"
				"\t\t\t<td>Документы специалистов экономической безопасности</td>\r\n"
				"\t\t</tr></table><br/>\r\n"
				// КНОПКА_ОТСЫЛАЕТ:
				// auth == '' (assigned)
				// view == '111' (assigned)
				// user == 'KurochkinSN' (assigned)
				// person == '╘рьшыш  ╚ь  ╬ЄўхёЄтю' (new string)
				// dognostn == '─юыцэюёЄ№' (new string)
				// office == '═ршьхэютрэшх яюфЁрчфхыхэш ' (new string)
				// kredit_w == 'on' (new string)
				// kassa_r == 'on' (new string)
				// btn == '> ═р яЁшэЄхЁ' (assigned)
				"\t\t<input type=\"submit\" name=\"btn\" value=\"> К печатной форме\" title=\"Сохранить и перейти к печатной форме\">\r\n"
				"\t</form>\r\n"
				, 'R'==*camera?on:off,   'R'==*camera?on:off 
				, 'R'==*security?on:off, 'R'==*security?on:off 
				);
	}
}

//
//!\brief	Редактированные поля сохранить в БД и сформировать близкую к утвержденной html-форму "Заявка на ФР"
//
//!\note	ДЛЯ КОРРЕКТНОЙ РАБОТЫ: в http_args должны быть переменные "pers" и "bran"
//
void UI_View111::ev_next(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	#ifdef _DEBUG
	function func("    "__FUNCTION__);
	#endif

	//
	// ИЗВЛЕКАЕМ_ДАННЫЕ_ИЗ_HTTP:
	// ковертируем http-переменные: oper_r=='on', scan_w == 'on'
	//    oper_r == 'on'
	//
	char const* const R = "R";
	char const* const W = "W";
	char const* const on = "on";
	char const* const off = " ";
	// если var_r=='on', то var='R' и все
	char const* kredit   = on==http_args("kredit_w")?W:(on==http_args("kredit_r")?R:off);
	char const* oper     = on==http_args("oper_w")?W:(on==http_args("oper_r")?R:off);
	char const* scan     = on==http_args("scan_w")?W:(on==http_args("scan_r")?R:off);
	char const* kassa    = on==http_args("kassa_w")?W:(on==http_args("kassa_r")?R:off);
	char const* foto     = on==http_args("foto_w")?W:(on==http_args("foto_r")?R:off);
	char const* uprav    = on==http_args("uprav_w")?W:(on==http_args("uprav_r")?R:off);
	char const* glavbuh  = on==http_args("glavbuh_w")?W:(on==http_args("glavbuh_r")?R:off);
	char const* office   = on==http_args("office_w")?W:(on==http_args("office_r")?R:off);
	char const* camera   = on==http_args("camera_w")?W:(on==http_args("camera_r")?R:off);
	char const* security = on==http_args("security_w")?W:(on==http_args("security_r")?R:off);
	char const* status   = "исполнено";

	//
	// ИЗВЛЕКАЕМ_ДАННЫЕ_ИЗ_БД:
	// зная "bran" (Энский) и "pers" (Logon-имя)
	//
	std::string sql_select_fileacc_str;
	::format(sql_select_fileacc_str, 
			"select FILACC_BRANCH_PREF, FILACC_USER_LOGON, FILACC_USER_NAME, FILACC_USER_POST" // [0]-[3]
			", FILACC_KREDIT, FILACC_OPER, FILACC_SCAN, FILACC_KASSA, FILACC_FOTO" // [4]-[8]
			", FILACC_UPRAV, FILACC_GLAVBUH, FILACC_OFFICE, FILACC_SECURITY" // [9]-[12]
			" from FILE_ACCESS where FILACC_BRANCH_PREF='%1' and FILACC_USER_LOGON='%2'"
			, http_args("bran"), http_args("pers")
			);
	DB_Dataset db_dataset = db_handle.exec_sql(sql_select_fileacc_str);
	int vars_not_match = 0;
	if( db_dataset.fetch() ) {
		// сравниваем первые символы строк полученных из БД и из http-переменных
		if( db_dataset.field(1, off)!=http_args("pers"))  ++vars_not_match;  // FILACC_USER_LOGON
		if( db_dataset.field(2, off)!=http_args("name"))  ++vars_not_match;  // FILACC_USER_NAME
		if( db_dataset.field(3, off)!=http_args("post"))  ++vars_not_match;  // FILACC_USER_POST
		// сравниваем первые символы строк полученных из БД и из http-переменных
		if( *db_dataset.field(4, off)!=*kredit)    ++vars_not_match;         // FILACC_KREDIT
		if( *db_dataset.field(5, off)!=*oper)      ++vars_not_match;         // FILACC_OPER
		if( *db_dataset.field(6, off)!=*scan)      ++vars_not_match;         // FILACC_SCAN
		if( *db_dataset.field(7, off)!=*kassa)     ++vars_not_match;         // FILACC_KASSA
		if( *db_dataset.field(8, off)!=*foto)      ++vars_not_match;         // FILACC_FOTO
		if( *db_dataset.field(9, off)!=*uprav)     ++vars_not_match;         // FILACC_UPRAV
		if( *db_dataset.field(10, off)!=*glavbuh)  ++vars_not_match;         // FILACC_GLAVBUH
		if( *db_dataset.field(11, off)!=*office)   ++vars_not_match;         // FILACC_OFFICE
		//if( *db_dataset.field(0, off)!=*camera)    ++vars_not_match;         // FILACC_CAMERA
		if( *db_dataset.field(12, off)!=*security) ++vars_not_match;         // FILACC_SECURITY

//vars_not_match = 0;
		if( vars_not_match ) {
			std::string sql_select_fileacc_str;
			// требуется SQL::UPDATE bkb
			::format(sql_select_fileacc_str, 
					"delete from FILE_ACCESS where FILACC_BRANCH_PREF='%1' and FILACC_USER_LOGON='%2'"
					, http_args("bran"), http_args("pers")
					);
			DB_Dataset db_dataset = db_handle.exec_sql(sql_select_fileacc_str);
			db_dataset.fetch();
			goto sql_insert_fileacc;
		}
	} else {
		sql_insert_fileacc:
		std::string sql_select_fileacc_str;
		::format(sql_select_fileacc_str, 
				"insert into FILE_ACCESS values("
				"'%1', '%2', '%3', '%4', "       // FILACC_BRANCH_PREF, FILACC_USER_LOGON, FILACC_USER_NAME, FILACC_USER_POST
				"'%5', '%6', '%7', '%8', '%9', " // FILACC_KREDIT, FILACC_OPER, FILACC_SCAN, FILACC_KASSA, FILACC_FOTO
				, http_args("bran")
				, http_args("pers")
				, http_args("name")
				, http_args("post")
				, kredit, oper, scan, kassa, foto
				);
		::format(sql_select_fileacc_str, 
				"'%1', '%2', '%3', '%4', '%5')" // FILACC_UPRAV, FILACC_GLAVBUH, FILACC_OFFICE, FILACC_CAMERA, FILACC_SECURITY
				, uprav, glavbuh, office, camera, security, status 
				);
		//#ifdef _DEBUG
		//{::Sleep(10); FILETIME ft; ::GetSystemTimeAsFileTime(&ft);
		//std::string file_name_r; ::format(file_name_r, "%1%2-INSERT.txt", (void*)ft.dwHighDateTime, (void*)ft.dwLowDateTime);
		//File<FileOpening::CreateAlways, FileAccess::ReadWrite, FileShare::ShareReadWriteDelete> file_r(file_name_r.c_str());
		//file_r.write(sql_select_fileacc_str.c_str(), sql_select_fileacc_str.size());}
		//#endif
		DB_Dataset db_dataset_fileacc = db_handle.exec_sql(sql_select_fileacc_str);
		db_dataset_fileacc.fetch();
	}

	#ifdef _DEBUG 
	{ std::string deb_out;
	 // Kredit ! Oper ! Scan ! Kassa ! Foto ! Uprav ! Glavbuh ! Office ! Camera$ ! Security
	::format(deb_out, "vars|Kredit|Oper|Scan|Kassa|Foto|Uprav|Glavbuh|Office|Camera$|Security|\n", 0);
	::OutputDebugString(deb_out.c_str());
	deb_out.clear();
	::format(deb_out, 
			"http|   %1  |  %2 |  %3 |  %4  |  %5 |  %6  |   %7   |   %8  |   X   |    %9   |\n"
			, kredit, oper, scan, kassa, foto, uprav, glavbuh, office, security
			);
	::OutputDebugString(deb_out.c_str());
	deb_out.clear();
	::format(deb_out, 
			"_db_|   %1  |  %2 |  %3 |  %4  |  %5 |  %6  |   %7   |   %8  |   X   |    %9   |\n"
			, db_dataset.field(4, off), db_dataset.field(5, off), db_dataset.field(6, off)
			, db_dataset.field(7, off), db_dataset.field(8, off), db_dataset.field(9, off)
			, db_dataset.field(10, off), db_dataset.field(11, off), db_dataset.field(12, off)
			);
	::OutputDebugString(deb_out.c_str()); }
	#endif
/*
		<input type="hidden" name="view" value="11">
		<input type="hidden" name="user" value="KurochkinSN">
		<input type="submit" name="btn" value="<" title="Назад">

		<input type="submit" name="btn" value="1) Файловый доступ" class="cell_btn" title="Заявка 1) Файловый доступ"/
*/
	int next_view = 11;
	::format(html_output,
			#ifdef _DEBUG
			"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
			#endif
			"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
			"\t\t<input type=\"hidden\" name=\"auth\" value=\"%1\">\r\n"
			"\t\t<input type=\"hidden\" name=\"view\" value=\"%2\">\r\n"
			"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
			"\t\t<input type=\"submit\" name=\"btn\" value=\"1) Заявка\" title=\"Назад\" class=\"cell_btn\">\r\n"
			//"\t\t<b><u>Заявка</u></b>\r\n"
			"\t</form>\r\n"
			"\t\t<p><font size=\"+1\">На предоставление/изменение прав доступа<br/>к файловым ресурсам офиса ОАО &ldquo;СКБ-банк&rdquo;</font></p>\r\n"
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\"><tr>\r\n"
			"\t\t\t<td>Сотрудник:</td>\r\n"
			"\t\t\t<td><font size=\"+1\">%6</font>;&nbsp;&nbsp;<font size=\"+1\">%5</font></td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td>&nbsp;</td>\r\n"
			"\t\t\t<td valign=\"top\"><font size=\"-2\">(ФИО, электронный адрес)</font></td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td>Должность:</td>\r\n"
			"\t\t\t<td><font size=\"+1\">%7</font></td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td>&nbsp;</td>\r\n"
			"\t\t\t<td valign=\"top\"><font size=\"-2\">(должность сотрудника)</font></td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td>Подразделение:</td>\r\n"
			"\t\t\t<td style=\"background-color: #ffffc0; border: 1px solid #0000ff\"><font size=\"+1\">%4</font></td>\r\n" 
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td>&nbsp;</td>\r\n"
			"\t\t\t<td valign=\"top\"><font size=\"-2\">(наименование структурного подразделения)</font></td>\r\n"
			"\t\t</tr></table>\r\n"
			"\t\t<p><b><i>Категория доступа к документам:</i></b></p>\r\n"
			, http_args("auth")
			, next_view
			, http_args("user")
			, http_args("offi")
			, http_args("pers")
			, http_args("name")
			, http_args("post")
			);
			//"\t\t\t<td style=\"background-color: #ffffc0; border: 1px solid #0000ff\">R</td><td>W</td>\r\n"

	char const* const on_ = "V";
	char const* const off_ = "-";
	::format(html_output,
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\" border=\"0\"><tr>\r\n"
			"\t\t\t<td align=\"right\"><b>Д&nbsp;о&nbsp;с</b><br/><font size=\"-2\">Чтение&nbsp;</td><td align=\"left\"><b>т&nbsp;у&nbsp;п&nbsp;</b><br/><font size=\"-2\">Запись</td><td><b>К&nbsp;а&nbsp;т&nbsp;а&nbsp;л&nbsp;о&nbsp;г&nbsp;</b></td><td><b>Н&nbsp;а&nbsp;з&nbsp;н&nbsp;а&nbsp;ч&nbsp;е&nbsp;н&nbsp;и&nbsp;е</b></td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%1</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%2</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Kredit</b></td>\r\n"
			"\t\t\t<td>Обмен информацией специалистов кредитного сектора</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%3</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%4</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Oper</b></td>\r\n"
			"\t\t\t<td>Обмен информацией специалистов операционного сектора</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%5</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%6</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Scan</b></td>\r\n"
			"\t\t\t<td>Скан-копии документов для отправки, с разбиением на подкаталоги в формате YYYY-MM-DD</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%7</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%8</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Kassa</b></td>\r\n"
			"\t\t\t<td>Обмен информацией специалистов кассового узла</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			, 'R'==*kredit?on_:off_, 'W'==*kredit?on_:off_
			, 'R'==*oper?on_:off_,   'W'==*oper?on_:off_
			, 'R'==*scan?on_:off_,   'W'==*scan?on_:off_
			, 'R'==*kassa?on_:off_,  'W'==*kassa?on_:off_
			);

	::format(html_output,
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%1</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%2</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Foto</b></td>\r\n"
			"\t\t\t<td>Каталог с фото банкоматов, мероприятий в банке, и т.д.</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%3</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%4</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Uprav</b></td>\r\n"
			"\t\t\t<td>Документы руководства офиса</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%5</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%6</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Glavbuh</b></td>\r\n"
			"\t\t\t<td>Документы главного бухгалтера</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%7</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%8</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Office</b></td>\r\n"
			"\t\t\t<td>Документы общего назначения</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			, 'R'==*foto?on_:off_,    'W'==*foto?on_:off_
			, 'R'==*uprav?on_:off_,   'W'==*uprav?on_:off_
			, 'R'==*glavbuh?on_:off_, 'W'==*glavbuh?on_:off_
			, 'R'==*office?on_:off_,  'W'==*office?on_:off_
			);

	::format(html_output,
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%1</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%2</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Camera$</b></td>\r\n"
			"\t\t\t<td>Ресурс для размещения фотографий клиентов при оформлении кредитов</td>\r\n"
			"\t\t\t</tr><tr>\r\n"
			"\t\t\t<td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%3</b></font>&nbsp;</div></td><td><div class=\"tbl_cell\">&nbsp;<font face=\"Courier\"><b>%4</b></font>&nbsp;</div></td>\r\n"
			"\t\t\t<td><b>Security</b></td>\r\n"
			"\t\t\t<td>Документы специалистов экономической безопасности</td>\r\n"
			"\t\t\t</tr></table>\r\n"
			, 'R'==*camera?on_:off_,   'R'==*camera?on_:off_ 
			, 'R'==*security?on_:off_, 'R'==*security?on_:off_ 
			);
}

/*
ЗДЕСЬ ЕСТЬ 
	bran - необходимо заполнять подразделение
ЗДЕСЬ МОЖЕТ БЫТЬ
	pers - необходимо извлекать установленные в БД права, дату их установки и картинку с файлом или ссылку для ускорения филиалов
*/
	//! если http_args[bran] непустое, то извлекаем из БД полное наименования филиала/офиса
	/*  ЕСТЬ АЛЬТЕРНАТИВА ПЕРЕДАВАТЬ ЧЕРЕЗ http_args
	std::string branch_name_str("Наименование подразделения");
	if( !ui_cont_ptr->get_bran_str().empty() ) {
		std::string sql_select_branch_str;
		::format(sql_select_branch_str, 
				"select BRANCH_PREF, BRANCH_TYPE, BRANCH_NAME from BRANCHES where BRANCH_PREF='%1'"
				, ui_cont_ptr->get_bran_str()
		);
		DB_Dataset db_dataset_branch_name = ui_cont_ptr->db_handle().exec_sql(sql_select_branch_str);
		if( db_dataset_branch_name.fetch() ) {
			if( db_dataset_branch_name.field(1) ) branch_name_str.assign(db_dataset_branch_name.field(1));
			branch_name_str.append(" ");
			if( db_dataset_branch_name.field(2) ) branch_name_str.append(db_dataset_branch_name.field(2));
		}
	} else {
		ui_cont_ptr->html_output().append("не указано dns-имя офиса/филиала"); 
		return;
	}*/

	/*
	//! если http_args[pers] непустое, то извлекаем из БД фио и должность
	//  ЕСТЬ АЛЬТЕРНАТИВА ПЕРЕДАВАТЬ ЧЕРЕЗ http_args
	std::string pers_str("Email");
	std::string pers_post_str("Должность");
	std::string pers_name_str("Фамилия Имя Отчество");
	if( !http_args("pers").empty() ) {
		std::string sql_select_fileacc_pers_name_str;
		::format(sql_select_fileacc_pers_name_str, 
				"select FILACC_USER_LOGON, FILACC_USER_NAME, FILACC_USER_POST from FILE_ACCESS where FILACC_BRANCH_PREF='%1' and FILACC_USER_LOGON='%2'"
				, http_args("bran")
				, http_args("pers")
		);
		DB_Dataset db_dataset_pers_name = db_handle.exec_sql(sql_select_fileacc_pers_name_str);
		if( db_dataset_pers_name.fetch() ) {
			if( db_dataset_pers_name.field(0) ) pers_str.assign(db_dataset_pers_name.field(0));
			if( db_dataset_pers_name.field(1) ) pers_name_str.assign(db_dataset_pers_name.field(1));
			if( db_dataset_pers_name.field(2) ) pers_post_str.assign(db_dataset_pers_name.field(1));
		}
	}
	*/

