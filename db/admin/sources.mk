db_admin_sh_sources = \
	$(top_srcdir)/db/admin/clean_all_tables.sh \
	$(top_srcdir)/db/admin/clean_a_table.sh \
	$(top_srcdir)/db/admin/count_all_tables.sh \
	$(top_srcdir)/db/admin/count_a_table.sh \
	$(top_srcdir)/db/admin/create_airinv_db.sh \
	$(top_srcdir)/db/admin/create_airinv_user.sh \
	$(top_srcdir)/db/admin/create_dsim_db.sh \
	$(top_srcdir)/db/admin/create_dsim_user.sh \
	$(top_srcdir)/db/admin/dump_airinv_db_structure.sh \
	$(top_srcdir)/db/admin/dump_dsim_db_structure.sh \
	$(top_srcdir)/db/admin/load_airinv_dsim_data.sh \
	$(top_srcdir)/db/admin/load_dsim_data.sh
db_admin_sql_sources = \
	$(top_srcdir)/db/admin/create_airinv_tables.sql \
	$(top_srcdir)/db/admin/create_airinv_user.sql \
	$(top_srcdir)/db/admin/create_dsim_tables.sql \
	$(top_srcdir)/db/admin/create_dsim_user.sql \
	$(top_srcdir)/db/admin/fill_airinv_tables.sql \
	$(top_srcdir)/db/admin/fill_dsim_tables.sql
