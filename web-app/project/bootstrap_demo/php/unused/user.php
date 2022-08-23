<?php namespace User;
require_once("create_table.php");
require_once("drop_table.php");
require_once("show_table.php");
require_once("mysql.php");
require_once("website.php");
require_once("range.php");
const NAME = 'user';
const TABLE_NAME = \Website::TABLE_NAME.'_'.\User\NAME;
class Id {
    public const NAME  = 'id';
    public const TYPE  = 'INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY';
    public const FIELD = Id::NAME.' '.Id::TYPE;
}
class Name {
    public const NAME  = 'name';
    public const RANGE = [6,32];
    public const TYPE  = 'VARCHAR('.Name::RANGE[MAX].') NOT NULL';
    public const FIELD = Name::NAME.' '.Name::TYPE;
}
class Password {
    public const NAME  = 'password';
    public const RANGE = [6,32];
    public const TYPE  = 'VARCHAR('.Password::RANGE[MAX].') NOT NULL';
    public const FIELD = Password::NAME.' '.Password::TYPE;
}
class Admin {
    public const NAME  = 'admin';
    public const TYPE  = 'BOOL NOT NULL DEFAULT FALSE';
    public const FIELD = Admin::NAME.' '.Admin::TYPE;
}
function create_table() {
    \create_table(
        \User\TABLE_NAME, 
        \User\Id::FIELD, 
        \User\Name::FIELD, 
        \User\Password::FIELD,
        \User\Admin::FIELD
    );
}
function drop_table() {\drop_table(\User\TABLE_NAME);}
function show_table() {\show_table(\User\TABLE_NAME);}

switch($_GET['action']) {
    case 'create_table' : \User\create_table(); break;
    case 'drop_table'   : \User\drop_table();   break;
    case 'show_table'   : \User\show_table();   break;
    default             :                       break;
}
?>