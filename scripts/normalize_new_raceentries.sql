# This takes a denormalized race entries table (hist_new_raceentries)
# (that is, one with all of the team member person ids encoded into the table itself)
# and splits it into a normalized race entries table for production use, as well as a
# MxN mapping table
#
# Any existing contents of those tables are undisturbed, we just insert new rows.  Look out for duplicate data!
#
# THIS SCRIPT DOES NOT DROP THE TEMP TABLE, YOU MUST DO THAT YOURSELF:
# DROP TABLE hist_new_raceentries;
#

# This is the same as the input table, but with all of the peoplecolums (e.g. PreDriver) removed.
CREATE TABLE IF NOT EXISTS `hist_raceentries` (
  `entryid` varchar(12) NOT NULL,
  `Year` int(11) DEFAULT NULL,
  `orgid` varchar(5) DEFAULT NULL,
  `Class` text,
  `Team` text,
  `Place` int(11) DEFAULT NULL,
  `buggyid` varchar(25) DEFAULT NULL,
  `Prelim` double DEFAULT NULL,
  `Reroll` double DEFAULT NULL,
  `Final` double DEFAULT NULL,
  `FinalReroll` double DEFAULT NULL,
  `DQ` text,
  `Note` text,
  PRIMARY KEY (`entryid`),
  INDEX(`year`),
  INDEX(`orgid`),
  INDEX(`buggyid`),
  UNIQUE KEY `entryid_UNIQUE` (`entryid`)
);

CREATE TABLE IF NOT EXISTS `hist_entrypeoplemap` (
    id INT AUTO_INCREMENT PRIMARY KEY,
    personid VARCHAR(20) NOT NULL,
    entryid VARCHAR(12) NOT NULL,
    heattype ENUM('Prelim', 'Prelim Reroll', 'Final', 'Final Reroll') NOT NULL,
    position ENUM('Driver', 'Hill 1', 'Hill 2', 'Hill 3', 'Hill 4', 'Hill 5') NOT NULL,
    INDEX (`personid`),
    INDEX (`entryid`)
);

START TRANSACTION;
INSERT INTO hist_raceentries
   SELECT entryid, Year, orgid, Class, Team, Place, buggyid, Prelim, Reroll, Final, FinalReroll, DQ, Note
     FROM hist_new_raceentries;

# Drivers
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT PreDriver, entryid, 'Prelim', 'Driver' FROM hist_new_raceentries
    WHERE PreDriver IS NOT NULL AND PreDriver != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT RRDriver, entryid, 'Prelim Reroll', 'Driver' FROM hist_new_raceentries
    WHERE RRDriver IS NOT NULL AND RRDriver != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinDriver, entryid, 'Final', 'Driver' FROM hist_new_raceentries
    WHERE FinDriver IS NOT NULL AND FinDriver != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinRRDriver, entryid, 'Final Reroll', 'Driver' FROM hist_new_raceentries
    WHERE FinRRDriver IS NOT NULL AND FinRRDriver != 0;

# Hill 1
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT PreH1, entryid, 'Prelim', 'Hill 1' FROM hist_new_raceentries
    WHERE PreH1 IS NOT NULL AND PreH1 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT RRH1, entryid, 'Prelim Reroll', 'Hill 1' FROM hist_new_raceentries
    WHERE RRH1 IS NOT NULL AND RRH1 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinH1, entryid, 'Final', 'Hill 1' FROM hist_new_raceentries
    WHERE FinH1 IS NOT NULL AND FinH1 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinRRH1, entryid, 'Final Reroll', 'Hill 1' FROM hist_new_raceentries
    WHERE FinRRH1 IS NOT NULL AND FinRRH1 != 0;

# Hill 2
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT PreH2, entryid, 'Prelim', 'Hill 2' FROM hist_new_raceentries
    WHERE PreH2 IS NOT NULL AND PreH2 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT RRH2, entryid, 'Prelim Reroll', 'Hill 2' FROM hist_new_raceentries
    WHERE RRH2 IS NOT NULL AND RRH2 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinH2, entryid, 'Final', 'Hill 2' FROM hist_new_raceentries
    WHERE FinH2 IS NOT NULL AND FinH2 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinRRH2, entryid, 'Final Reroll', 'Hill 2' FROM hist_new_raceentries
    WHERE FinRRH2 IS NOT NULL AND FinRRH2 != 0;

# Hill 3
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT PreH3, entryid, 'Prelim', 'Hill 3' FROM hist_new_raceentries
    WHERE PreH3 IS NOT NULL AND PreH3 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT RRH3, entryid, 'Prelim Reroll', 'Hill 3' FROM hist_new_raceentries
    WHERE RRH3 IS NOT NULL AND RRH3 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinH3, entryid, 'Final', 'Hill 3' FROM hist_new_raceentries
    WHERE FinH3 IS NOT NULL AND FinH3 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinRRH3, entryid, 'Final Reroll', 'Hill 3' FROM hist_new_raceentries
    WHERE FinRRH3 IS NOT NULL AND FinRRH3 != 0;

# Hill 4
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT PreH4, entryid, 'Prelim', 'Hill 4' FROM hist_new_raceentries
    WHERE PreH4 IS NOT NULL AND PreH4 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT RRH4, entryid, 'Prelim Reroll', 'Hill 4' FROM hist_new_raceentries
    WHERE RRH4 IS NOT NULL AND RRH4 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinH4, entryid, 'Final', 'Hill 4' FROM hist_new_raceentries
    WHERE FinH4 IS NOT NULL AND FinH4 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinRRH4, entryid, 'Final Reroll', 'Hill 4' FROM hist_new_raceentries
    WHERE FinRRH4 IS NOT NULL AND FinRRH4 != 0;

# Hill 5
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT PreH5, entryid, 'Prelim', 'Hill 5' FROM hist_new_raceentries
    WHERE PreH5 IS NOT NULL AND PreH5 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT RRH5, entryid, 'Prelim Reroll', 'Hill 5' FROM hist_new_raceentries
    WHERE RRH5 IS NOT NULL AND RRH5 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinH5, entryid, 'Final', 'Hill 5' FROM hist_new_raceentries
    WHERE FinH5 IS NOT NULL AND FinH5 != 0;
INSERT INTO hist_entrypeoplemap (personid, entryid, heattype, position)
   SELECT FinRRH5, entryid, 'Final Reroll', 'Hill 5' FROM hist_new_raceentries
    WHERE FinRRH5 IS NOT NULL AND FinRRH5 != 0;

COMMIT;
