##jcSQL##

This project is a simple implementation of a executable engine of SQL which matches my own interest.

###jcSQL's first stage of the representation :###

> select <- student name age 
> =>select name,age from student> 
>
> select <- student
> =>select * from student> 
>
> update <- student name='xxx' [age == 10] 
> =>update student set name = 'xxx' where age = 10> 
>
> delete <- student [ name == 'xxx']
> =>delete from student where name = 'xxx' > 
>
> create <- student string name int age [ name primary key]
> =>create table student (name string,age int,primary key(name))> 
>
> insert into student (name,age) values('xxx',10)
> =>insert <- student name='xxx' age=xxx > 
>
> drop <- student
> =>drop table student> 
>
> alter table student add dept string
> =>alter<- student + string dept> 
>
> alter table student drop column dept
> =>alter<- student - string dept> 
>
> alter table student alter column dept int
> =>alter<- student / int dept

Well...this toy is incomplete and needs other key words,;p,maybe the grammar will be altered gradually during the development process of the compiler.  