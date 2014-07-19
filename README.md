##jcSQL##

This project is a simple implementation of a executable engine of SQL which matches my own interest.

###jcSQL's first stage of the representation :###

> select <- table_name column_names [column_name OP 'XXX' and column_name OP XXX or column_name OP {S}] 
  
> create <- table table_name type column_name type column_name  [ column_name not null , column_name primary key ] 
	    | database db_name ...

> insert <- table_name column_name='XXX' column_name=XXX ...

> update <- table_name column_name='XXX' column_name=XXX ... [column_name OP 'XXX' and/, column_name OP XXX or column_name OP {S}]

> delete <- table_name [column_name OP 'XXX' and column_name OP XXX or column_name OP {S}] 

> drop <- table table_name | database db_name

> alter <-  table_name type column_name  type column_name

> alter <-  table_name column_name column_name

> alter <-  table_name column_name type

> OP-> == != < > <= >= ...

Actually,it is incomplete and needs improving,;p

Well...maybe the grammar will be altered gradually during the development process of the compiler.  