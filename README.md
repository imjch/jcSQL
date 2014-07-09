##jcSQL##

This project is a simple implementation of a executable engine of SQL which matches my own interest.
<<<<<<< HEAD:README


###jcSQL's first stage of the representation :###

>> select <- table_name column_names [column_name OP 'XXX' and column_name OP XXX or column_name OP {S}] 


   create <- table table_name type column_name type column_name  [ column_name not null , column_name primary key ] 


   insert <- table_name column_name='XXX' column_name=XXX


   update <- table_name column_name='XXX' column_name=XXX  [column_name OP 'XXX' and/, column_name OP XXX or column_name OP {S}]


   delete <- table_name [column_name OP 'XXX' and column_name OP XXX or column_name OP {S}] 


   drop <- table table_name

   alter <-  table_name type column_name  type column_name
   alter <-  table_name column_name column_name
   alter <-  table_name column_name type


It is incomplete and needs improving,;p

Well...maybe the grammar will be altered gradually during the development process of the compiler.  
=======
>>>>>>> f9b5c56e320302931d7576d4334f5ada096f0539:README.md
