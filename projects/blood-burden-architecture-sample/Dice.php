<?php

class Dice
{
    public static function d6(int $count = 1): int
    {
        $total = 0;
        for ($i = 0; $i < $count; $i++) {
            $total += random_int(1, 6);
        }
        return $total;
    }

    public static function roll2d6(): int
    {
        return self::d6(2);
    }
}
