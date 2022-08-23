<?php namespace MySQL;
function PRIMARY_KEY(string $primary_key_name): string {
    return "PRIMARY_KEY ($primary_key_name)";
}
function FOREIGN_KEY(string $foreign_key_name, string $table_name, string $primary_key_name): string {
    return "FOREIGN_KEY ($foreign_key_name) REFERENCES $table_name($primary_key_name)";
}
?>