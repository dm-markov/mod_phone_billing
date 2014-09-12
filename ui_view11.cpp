#include "ui.hpp"

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"

/*!	Обработчик сообщения '1' от формы View0
 *******************************************
 *	1) Сформировать список текущих прав доступа и дать возможность его редактировать
 *	@param UI_Control_ указатель на автомат
 */
//! выдать список настроеных прав доступа
void UI_View11::ev_1(std::string& html_output, HttpArgs const& http_args, DB_Handle& db_handle) {
	#ifdef _DEBUG
	function func("    "__FUNCTION__);
	#endif


	//if( http_args("user").empty() ) throw std::exception(__FUNCTION__": Wrong incoming http-args, 'user' expected");
	//if( http_args("auth").empty() ) throw std::exception(__FUNCTION__": Wrong incoming http-args, 'auth' expected");
	int next_view = 111;
	::format(html_output,
			#ifdef _DEBUG
			"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
			#endif
			"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
			"\t\t<input type=\"hidden\" name=\"view\" value=\"%1\">\r\n" 
			"\t\t<input type=\"hidden\" name=\"auth\" value=\"%2\">\r\n"
			"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
			"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"Назад\">\r\n"
			"\t\t<b><u>Файловый доступ</u> --- текущие права доступа и статус выполнения заявок</b><br/>\r\n"
			"\t<form>\r\n"
//=			"\t\t<table border=\"1\" cellspacing=\"0\" cellpadding=\"1\"><tr>\r\n"
//=			"\t\t<th>Сотрудник</th><th>LogonName</th><th>Kredit</th><th>Oper</th><th>Kassa</th><th>Scan</th><th>Foto</th><th>Office</th><th>Security</th><th>Uprav</th><th>Glavbuh</th><th>IT</th>\r\n"
			, next_view
			, http_args("auth")
			, http_args("user")
	);

	//
	// НАРУЖНЫЙ_БД_ЦИКЛ:
	// пробегаем по филиалам закрепленным за ИТ-специалистом 
	// или управляющим и извлекаем наименование и тип филиала
	//
	std::string sql_select_branch_str;
	::format(sql_select_branch_str, 
			"select BRANCH_PREF, BRANCH_TYPE, BRANCH_NAME from BRANCHES, BRANCH_OWNERS where BRAOWN_BRANCH_PREF=BRANCH_PREF and BRAOWN_USER_LOGON='%1'"
			, http_args("user")
	);
	DB_Dataset db_dataset_branch = db_handle.exec_sql(sql_select_branch_str);
	while( db_dataset_branch.fetch() ) {
		::format(html_output,
				"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
				// КНОПКА: "Добавить сотрудника в офис" ОТСЫЛАЕТ:
				"		<input type=\"hidden\" name=\"auth\" value=\"%4\">\r\n"
				"		<input type=\"hidden\" name=\"view\" value=\"%5\">\r\n"
				"		<input type=\"hidden\" name=\"user\" value=\"%6\">\r\n"
				"		<input type=\"hidden\" name=\"bran\" value=\"%1\">\r\n"
				"		<input type=\"submit\" name=\"btn\" value=\"+\" title=\"Добавить сотрудника в '%2 %3'\">\r\n"
				"\t</form>\r\n"
				"\t\t<b>%2 %3</b>\r\n"
				"\t<table border=\"1\" cellspacing=\"0\" cellpadding=\"1\">\r\n"
				"\t<tr>\r\n"
				"\t\t<th>Сотрудник</th>\r\n"
				"\t\t<th>LogonName</th>\r\n"
				"\t\t<th>Kredit</th>\r\n"
				"\t\t<th>Oper</th>\r\n"
				"\t\t<th>Scan</th>\r\n"
				"\t\t<th>Kassa</th>\r\n"
				"\t\t<th>Foto</th>\r\n"
				"\t\t<th>Uprav</th>\r\n"
				"\t\t<th>Glavbuh</th>\r\n"
				"\t\t<th>Office</th>\r\n"
				"\t\t<th>Security</th>\r\n"
				, db_dataset_branch.field(0, "&nbsp;")
				, db_dataset_branch.field(1, "&nbsp;")
				, db_dataset_branch.field(2, "&nbsp;")
				, http_args("auth")
				, next_view
				, http_args("user")
				);
		//
		// ВНУТРЕННИЙ_БД_ЦИКЛ:
		// пробегаем по правам доступа сотрудников филиала
		//
		std::string sql_select_fileacc_str;
		::format(sql_select_fileacc_str, 
				"select FILACC_BRANCH_PREF, FILACC_USER_LOGON, FILACC_USER_NAME, FILACC_USER_POST" // [0]-[3]
				", FILACC_KREDIT, FILACC_OPER, FILACC_SCAN, FILACC_KASSA, FILACC_FOTO" // [4]-[8]
				", FILACC_UPRAV, FILACC_GLAVBUH, FILACC_OFFICE, FILACC_SECURITY" // [9]-[12]
				" from FILE_ACCESS where FILACC_BRANCH_PREF='%1'"
				, db_dataset_branch.field(0)
				);
		int count = 0;
		DB_Dataset db_dataset_fileacc = db_handle.exec_sql(sql_select_fileacc_str);
		while( db_dataset_fileacc.fetch() ) {
			// ФОРМИРУЕМ КНОПКУ "Посмотреть сотрудника офиса"
			::format(html_output,
					"\t</tr><tr>\r\n"
					"\t\t<td>\r\n"
					"\t\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
					"			<input type=\"hidden\" name=\"view\" value=\"%1\" />\r\n"
					"			<input type=\"hidden\" name=\"auth\" value=\"%2\" />\r\n"
					"			<input type=\"hidden\" name=\"user\" value=\"%3\" />\r\n"
					// http-переменные по текущему контексту выполнения
					"			<input type=\"hidden\" name=\"bran\" value=\"%4\" />\r\n"
					"			<input type=\"hidden\" name=\"pers\" value=\"%5\" />\r\n"
					"			<input type=\"submit\" name=\"btn\" value=\"%7. %6\" class=\"cell_btn\" />\r\n"
					"\t\t</form>\r\n"
					"\t\t</td>\r\n"
					"\t\t<td align=\"left\">&nbsp;%5</td>\r\n"
					, next_view
					, http_args("auth")
					, http_args("user")
					, db_dataset_fileacc.field(0, "&nbsp;") // FILACC_BRANCH_PREF
					, db_dataset_fileacc.field(1, "&nbsp;") // FILACC_USER_LOGON
					, db_dataset_fileacc.field(2, "&nbsp;") // FILACC_USER_NAME
					, ++count
					);
			//	Kredit Обмен информацией специалистов кредитного сектора 
			//	Oper Обмен информацией специалистов операционного сектора 
			//	Scan Скан-копии документов для отправки, с разбиением на подкаталоги в формате YYYY-MM-DD
			//	Kassa Обмен информацией специалистов кассового узла 
			//	Foto Каталог с фото банкоматов, мероприятий в банке, и т.д. 
			//	Uprav Документы руководства офиса 
			//	Glavbuh Документы главного бухгалтера 
			//	Office Документы общего назначения 
			//	Camera$ Ресурс для размещения фотографий клиентов при оформлении кредитов 
			//	Security 
			::format(html_output,
					//	Kredit, Oper, Kassa, Scan, Foto, Office, Security, Uprav, Glavbuh
					"\t\t<td align=\"center\">%1</td>\r\n"
					"\t\t<td align=\"center\">%2</td>\r\n"
					"\t\t<td align=\"center\">%3</td>\r\n"
					"\t\t<td align=\"center\">%4</td>\r\n"
					"\t\t<td align=\"center\">%5</td>\r\n"
					"\t\t<td align=\"center\">%6</td>\r\n"
					"\t\t<td align=\"center\">%7</td>\r\n"
					"\t\t<td align=\"center\">%8</td>\r\n"
					"\t\t<td align=\"center\">%9</td>\r\n"
					, db_dataset_fileacc.field(4, "&nbsp;")  // FILACC_KREDIT
					, db_dataset_fileacc.field(5, "&nbsp;")  // FILACC_OPER
					, db_dataset_fileacc.field(6, "&nbsp;")  // FILACC_SCAN
					, db_dataset_fileacc.field(7, "&nbsp;")  // FILACC_KASSA
					, db_dataset_fileacc.field(8, "&nbsp;")  // FILACC_FOTO
					, db_dataset_fileacc.field(9, "&nbsp;")  // FILACC_UPRAV
					, db_dataset_fileacc.field(10, "&nbsp;") // FILACC_GLAVBUH
					, db_dataset_fileacc.field(11, "&nbsp;") // FILACC_OFFICE
					// типа тут еще "Camera$" должна быть
					, db_dataset_fileacc.field(12, "&nbsp;") // FILACC_SECURITY
					);
		}
		html_output.append("\t\t</tr></table>\r\n");
	}
}
