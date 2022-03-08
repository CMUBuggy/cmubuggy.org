# Create an org logo table based on the images we have.
#
# Kept separate from the history database for management purposes, but in practice could be merged.

DROP TABLE IF EXISTS orglogos;

CREATE TABLE IF NOT EXISTS orglogos (
    orgid VARCHAR(15) PRIMARY KEY NOT NULL,
    image_url VARCHAR(2083)
);

START TRANSACTION;
INSERT INTO orglogos (orgid, image_url) VALUES ('AEP',  '/img/logos/aepi.jpg');
INSERT INTO orglogos (orgid, image_url) VALUES ('APX',  '/img/logos/apex.svg');
INSERT INTO orglogos (orgid, image_url) VALUES ('CIA',  '/img/logos/cia2022.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('CMTV', '/img/logos/cmutv.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('DG',   '/img/logos/dg.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('FRI',  '/img/logos/fringe.svg');
INSERT INTO orglogos (orgid, image_url) VALUES ('KS',   '/img/logos/kapsig.gif');
INSERT INTO orglogos (orgid, image_url) VALUES ('PKA',  '/img/logos/pikaracing.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('PIO',  '/img/logos/pioneers.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('RBO',  '/img/logos/robobuggy.svg');
INSERT INTO orglogos (orgid, image_url) VALUES ('SAE',  '/img/logos/sae.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('SDC',  '/img/logos/sdc.svg');
INSERT INTO orglogos (orgid, image_url) VALUES ('SEP',  '/img/logos/sigepracing.webp');
INSERT INTO orglogos (orgid, image_url) VALUES ('SN',   '/img/logos/signu.svg');
INSERT INTO orglogos (orgid, image_url) VALUES ('SPI',  '/img/logos/spirit.png');
INSERT INTO orglogos (orgid, image_url) VALUES ('W3VC', '/img/logos/w3vc.svg');
INSERT INTO orglogos (orgid, image_url) VALUES ('WRCT', '/img/logos/wrct2022.png');
COMMIT;
