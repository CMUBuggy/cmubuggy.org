CREATE TABLE IF NOT EXISTS `smugmug_comments` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    comment_id VARCHAR(15),
    comment_url VARCHAR(2083),
    thumbnail_url VARCHAR(2083),
    author VARCHAR(2083),
    comment VARCHAR(2083),
    created_at datetime,
    INDEX (`created_at` DESC)
);

CREATE TABLE IF NOT EXISTS `smugmug_uploads` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    gallery_url VARCHAR(2083),
    content_url VARCHAR(2083),
    thumbnail_url VARCHAR(2083),
    gallery_name VARCHAR(150),
    gallery_slug VARCHAR(300),
    photo_id VARCHAR(150),
    created_at datetime,
    INDEX (`created_at` DESC)
);