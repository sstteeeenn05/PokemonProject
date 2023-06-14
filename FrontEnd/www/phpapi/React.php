<?php
    class React{
        public static function resolve($message):void{
            exit("<span id='content' status='resolve'>".$message."</span>");
        }
        public static function reject($message):void{
            exit("<span id='content' status='reject'>".$message."</span>");
        }
        public static function arrayToDom($arr):string{
            return "<item>".implode('</item><item>',$arr)."</item>";
        }
    }
?>