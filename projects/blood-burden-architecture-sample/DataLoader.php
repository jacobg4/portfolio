<?php

class DataLoader
{
    public static function load(string $file): array
    {
        $path = __DIR__ . '/../data/' . $file;

        if (!file_exists($path)) {
            throw new RuntimeException("Data file not found: {$file}");
        }

        $data = json_decode(file_get_contents($path), true);

        if ($data === null) {
            throw new RuntimeException("Invalid JSON in: {$file}");
        }

        return $data;
    }
}
