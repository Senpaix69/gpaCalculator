DROP DATABASE IF EXISTS `gpacalculator`;
CREATE DATABASE `gpacalculator`;
USE `gpacalculator`;

CREATE TABLE `student`
(
  `regNo` VARCHAR(100) NOT NULL,
  `sname` VARCHAR(100) NOT NULL,
  `GPA` DECIMAL(10,2) NULL,
  `CGPA` DECIMAL(10,2) NULL,
  PRIMARY KEY (`regNo`)
);

CREATE TABLE `subject` 
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `creditHours` INT NOT NULL,
  `Percentage` DECIMAL (10, 2) NULL,
  `grade` VARCHAR(4) NULL,
  `gradePoints` DECIMAL(10,2) NULL,
  PRIMARY KEY (`subName`, `regNo`),
  CONSTRAINT `FK1` FOREIGN KEY (`regNo`) REFERENCES `student`(`regNo`) ON DELETE CASCADE
);

CREATE TABLE `assignment`
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `ID` INT NOT NULL AUTO_INCREMENT,
  `obtainNo` DECIMAL(10,2) NULL DEFAULT 0,
  `totalNo` DECIMAL(10,2) NULL DEFAULT 0,
  `obtainPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  `totalPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `subName`),
  CONSTRAINT `assignmentFK` FOREIGN KEY(`regNo`) REFERENCES
  `subject`(`regNo`) ON DELETE CASCADE
);
CREATE TABLE `assignmentnumbers`
(
  `assignmentID` INT NOT NULL,
  `numbers` DECIMAL(10,2) NULL DEFAULT 0,
  CONSTRAINT `assignNum` FOREIGN KEY(`assignmentID`)
  REFERENCES `assignment`(`ID`) ON DELETE CASCADE 
);

CREATE TABLE `quiz`
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `ID` INT NOT NULL AUTO_INCREMENT,
  `obtainNo` DECIMAL(10,2) NULL DEFAULT 0,
  `totalNo` DECIMAL(10,2) NULL DEFAULT 0,
  `obtainPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  `totalPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `subName`),
  CONSTRAINT `quizFK` FOREIGN KEY(`regNo`) REFERENCES
  `subject`(`regNo`) ON DELETE CASCADE
);
CREATE TABLE `quiznumbers`
(
  `quizID` INT NOT NULL,
  `numbers` DECIMAL(10,2) NULL DEFAULT 0,
  CONSTRAINT `quizNum` FOREIGN KEY(`quizID`)
  REFERENCES `quiz`(`ID`) ON DELETE CASCADE 
);

CREATE TABLE `cp`
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `ID` INT NOT NULL AUTO_INCREMENT,
  `obtainNo` DECIMAL(10,2) NULL DEFAULT 0,
  `totalNo` DECIMAL(10,2) NULL DEFAULT 0,
  `obtainPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  `totalPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `subName`),
  CONSTRAINT `cpFK` FOREIGN KEY(`regNo`) REFERENCES
  `subject`(`regNo`) ON DELETE CASCADE
);

CREATE TABLE `cpnumbers`
(
  `cpID` INT NOT NULL,
  `numbers` DECIMAL(10,2) NULL DEFAULT 0,
  CONSTRAINT `cpNum` FOREIGN KEY(`cpID`)
  REFERENCES `cp`(`ID`) ON DELETE CASCADE 
);

CREATE TABLE `mids`
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `ID` INT NOT NULL AUTO_INCREMENT,
  `obtainNo` DECIMAL(10,2) NULL DEFAULT 0,
  `totalNo` DECIMAL(10,2) NULL DEFAULT 0,
  `obtainPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  `totalPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `subName`),
  CONSTRAINT `midsFK` FOREIGN KEY(`regNo`) REFERENCES
  `subject`(`regNo`) ON DELETE CASCADE
);
CREATE TABLE `midsnumbers`
(
  `midsID` INT NOT NULL,
  `numbers` DECIMAL(10,2) NULL DEFAULT 0,
  CONSTRAINT `midsNum` FOREIGN KEY(`midsID`)
  REFERENCES `mids`(`ID`) ON DELETE CASCADE 
);

CREATE TABLE `finals`
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `ID` INT NOT NULL AUTO_INCREMENT,
  `obtainNo` DECIMAL(10,2) NULL DEFAULT 0,
  `totalNo` DECIMAL(10,2) NULL DEFAULT 0,
  `obtainPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  `totalPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `subName`),
  CONSTRAINT `finalsFK` FOREIGN KEY(`regNo`) REFERENCES
  `subject`(`regNo`) ON DELETE CASCADE
);
CREATE TABLE `finalsnumbers`
(
  `finalsID` INT NOT NULL,
  `numbers` DECIMAL(10,2) NULL DEFAULT 0,
  CONSTRAINT `finalsNum` FOREIGN KEY(`finalsID`)
  REFERENCES `finals`(`ID`) ON DELETE CASCADE 
);

CREATE TABLE `projectPresentation`
(
  `regNo` VARCHAR(100) NOT NULL,
  `subName` VARCHAR(100) NOT NULL,
  `ID` INT NOT NULL AUTO_INCREMENT,
  `obtainNo` DECIMAL(10,2) NULL DEFAULT 0,
  `totalNo` DECIMAL(10,2) NULL DEFAULT 0,
  `obtainPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  `totalPercentage` DECIMAL(10,2) NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `subName`),
  CONSTRAINT `projectPresentationFK` FOREIGN KEY(`regNo`) REFERENCES
  `subject`(`regNo`) ON DELETE CASCADE
);
CREATE TABLE `projectPresentationNumbers`
(
  `projectPresentationID` INT NOT NULL,
  `numbers` DECIMAL(10,2) NULL DEFAULT 0,
  CONSTRAINT `projectPresentationNum` FOREIGN KEY(`projectPresentationID`)
  REFERENCES `projectPresentation`(`ID`) ON DELETE CASCADE 
);

DELIMITER // 
CREATE PROCEDURE `InsertAssignment`(IN reg varchar(100),IN subN varchar(100), IN TNO DECIMAL(10, 2), IN TP DECIMAL(10, 2))
BEGIN
	INSERT INTO `assignment` (`regNo`,`subName`, `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage`)
    VALUES (reg, subN, NULL, TNO, NULL, TP);
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `InsertCP`(IN reg varchar(100), IN subN varchar(100), IN TNO DECIMAL(10, 2), IN TP DECIMAL(10, 2))
BEGIN
	INSERT INTO `CP` (`regNo`,`subName`, `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage`)
    VALUES (reg, subN, NULL, TNO, NULL, TP);
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `InsertMids`(IN reg varchar(100), IN subN varchar(100), IN TNO DECIMAL(10, 2), IN TP DECIMAL(10, 2))
BEGIN
	INSERT INTO `mids` (`regNo`,`subName`, `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage`)
    VALUES (reg, subN, NULL, TNO, NULL, TP);
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `InsertQuiz`(IN reg varchar(100), IN subN varchar(100), IN TNO DECIMAL(10, 2), IN TP DECIMAL(10, 2))
BEGIN
	INSERT INTO `quiz` (`regNo`,`subName`, `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage`)
    VALUES (reg, subN, NULL, TNO, NULL, TP);
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `InsertFinals`(IN reg varchar(100), IN subN varchar(100), IN TNO DECIMAL(10, 2), IN TP DECIMAL(10, 2))
BEGIN
	INSERT INTO `finals` (`regNo`,`subName`, `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage`)
    VALUES (reg, subN, NULL, TNO, NULL, TP);
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `InsertProjectPresentation`(IN reg varchar(100), IN subN varchar(100), IN TNO DECIMAL(10, 2), IN TP DECIMAL(10, 2))
BEGIN
	INSERT INTO `projectpresentation` (`regNo`,`subName`, `obtainNo`, `totalNo`, `obtainPercentage`, `totalPercentage`)
    VALUES (reg, subN, NULL, TNO, NULL, TP);
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `UpdateAssignment`(IN id INT, IN subN VARCHAR(100))
BEGIN
	DECLARE s DECIMAL(10, 2) DEFAULT 0;
    DECLARE p DECIMAL(10, 2) DEFAULT 0;
	SET SQL_SAFE_UPDATES = 0;
    SELECT SUM(`numbers`) INTO s FROM `assignmentNumbers` WHERE `assignmentID` = id;
    UPDATE `assignment` SET `obtainNo` = s WHERE `ID` = id AND `subName` = subN;
    SELECT ((`obtainNo` / `totalNo`) * `totalPercentage`) INTO p FROM `assignment` WHERE `ID` = id AND `subName` = subN;
    UPDATE `assignment` SET `obtainPercentage` = p WHERE `ID` = id AND `subName` = subN;
	SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `UpdateCP`(IN id INT, IN subN VARCHAR(100))
BEGIN
	DECLARE s DECIMAL(10, 2) DEFAULT 0;
    DECLARE p DECIMAL(10, 2) DEFAULT 0;
	SET SQL_SAFE_UPDATES = 0;
    SELECT SUM(`numbers`) INTO s FROM `cpNumbers` WHERE `cpID` = id;
    UPDATE `cp` SET `obtainNo` = s WHERE `ID` = id AND `subName` = subN;
    SELECT ((`obtainNo` / `totalNo`) * `totalPercentage`) INTO p from `cp` WHERE `ID` = id AND `subName` = subN;
    UPDATE `cp` SET `obtainPercentage` = p WHERE `ID` = id AND `subName` = subN;
	SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `UpdateQuiz`(IN id INT, IN subN VARCHAR(100))
BEGIN
	DECLARE s DECIMAL(10, 2) DEFAULT 0;
    DECLARE p DECIMAL(10, 2) DEFAULT 0;
	SET SQL_SAFE_UPDATES = 0;
    SELECT SUM(`numbers`) INTO s FROM `quizNumbers` WHERE `quizID` = id;
    UPDATE `quiz` SET `obtainNo` = s WHERE `ID` = id AND `subName` = subN;
    SELECT ((`obtainNo` / `totalNo`) * `totalPercentage`) INTO p from `quiz` WHERE `ID` = id AND `subName` = subN;
    UPDATE `quiz` SET `obtainPercentage` = p WHERE `ID` = id AND `subName` = subN;
	SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `UpdateMids`(IN id INT, IN subN VARCHAR(100))
BEGIN
	DECLARE s DECIMAL(10, 2) DEFAULT 0;
    DECLARE p DECIMAL(10, 2) DEFAULT 0;
	SET SQL_SAFE_UPDATES = 0;
    SELECT SUM(`numbers`) INTO s FROM `midsNumbers` WHERE `midsID` = id;
    UPDATE `mids` SET `obtainNo` = s WHERE `ID` = id AND `subName` = subN;
    SELECT ((`obtainNo` / `totalNo`) * `totalPercentage`) INTO p from `mids` WHERE `ID` = id AND `subName` = subN;
    UPDATE `mids` SET `obtainPercentage` = p WHERE `ID` = id AND `subName` = subN;
	SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `UpdateFinals`(IN id INT, IN subN VARCHAR(100))
BEGIN
	DECLARE s DECIMAL(10, 2) DEFAULT 0;
    DECLARE p DECIMAL(10, 2) DEFAULT 0;
	SET SQL_SAFE_UPDATES = 0;
    SELECT SUM(`numbers`) INTO s FROM `finalsNumbers` WHERE `finalsID` = id;
    UPDATE `finals` SET `obtainNo` = s WHERE `ID` = id AND `subName` = subN;
    SELECT ((`obtainNo` / `totalNo`) * `totalPercentage`) INTO p from `finals` WHERE `ID` = id AND `subName` = subN;
    UPDATE `finals` SET `obtainPercentage` = p WHERE `ID` = id AND `subName` = subN;
	SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `UpdateProjectPresentation`(IN id INT, IN subN VARCHAR(100))
BEGIN
	DECLARE s DECIMAL(10, 2) DEFAULT 0;
    DECLARE p DECIMAL(10, 2) DEFAULT 0;
	SET SQL_SAFE_UPDATES = 0;
    SELECT SUM(`numbers`) INTO s FROM `projectPresentationNumbers` WHERE `projectPresentationID` = id;
    UPDATE `projectPresentation` SET `obtainNo` = s WHERE `ID` = id AND `subName` = subN;
    SELECT ((`obtainNo` / `totalNo`) * `totalPercentage`) INTO p from `projectPresentation` WHERE `ID` = id AND `subName` = subN;
    UPDATE `projectPresentation` SET `obtainPercentage` = p WHERE `ID` = id AND `subName` = subN;
	SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER // 
CREATE PROCEDURE `calculateSubjectPercentage`(IN reg VARCHAR(100), IN subN VARCHAR(100))
BEGIN
	DECLARE percAss DECIMAL(10, 2) DEFAULT 0;
	DECLARE percCP DECIMAL(10, 2) DEFAULT 0;
	DECLARE percMids DECIMAL(10, 2) DEFAULT 0;
	DECLARE percFinals DECIMAL(10, 2) DEFAULT 0;
	DECLARE percQuiz DECIMAL(10, 2) DEFAULT 0;
	DECLARE percPr DECIMAL(10, 2) DEFAULT 0;
    DECLARE TotalPerc DECIMAL(10, 2) DEFAULT 0;
    SET SQL_SAFE_UPDATES = 0;
	SELECT `obtainPercentage` INTO percAss FROM `assignment` WHERE `regNo` = reg AND `subName` = subN;
    SELECT `obtainPercentage` INTO percCP FROM `cp` WHERE `regNo` = reg AND `subName` = subN;
    SELECT `obtainPercentage` INTO percMids FROM `mids` WHERE `regNo` = reg AND `subName` = subN;
    SELECT `obtainPercentage` INTO percFinals FROM `finals` WHERE `regNo` = reg AND `subName` = subN;
    SELECT `obtainPercentage` INTO percQuiz FROM `quiz` WHERE `regNo` = reg AND `subName` = subN;
    SELECT `obtainPercentage` INTO percPr FROM `projectPresentation` WHERE `regNo` = reg AND `subName` = subN;
	SELECT (percAss + percCP + percQuiz + percMids + percFinals + percPr) INTO TotalPerc;
    UPDATE `subject` SET `Percentage` = TotalPerc WHERE `regNo` = reg AND `subName` = subN;
    SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER //
CREATE PROCEDURE `calculateGradeAndGradePoints` (IN reg VARCHAR(100), IN subN VARCHAR(100))
BEGIN
	DECLARE TotalPerc DECIMAL(10, 2) DEFAULT 0;
    DECLARE gradePoint DECIMAL(10, 2) DEFAULT 0;
    DECLARE grad VARCHAR(4);
	SET SQL_SAFE_UPDATES = 0;
    SELECT `percentage` INTO TotalPerc FROM `subject` where `regNo` = reg AND `subName` = subN;
    IF TotalPerc >= 86 AND TotalPerc <= 100 THEN
		SELECT "A" INTO grad;
        SELECT 4.0 INTO gradePoint;
	ELSEIF TotalPerc >= 82 AND TotalPerc <= 85 THEN
		SELECT "A-" INTO grad;
        SELECT 3.67 INTO gradePoint;
	ELSEIF TotalPerc >= 78 AND TotalPerc <= 81 THEN
		SELECT "B+" INTO grad;
        SELECT 3.33 INTO gradePoint;
	ELSEIF TotalPerc >= 74 AND TotalPerc <= 77 THEN
		SELECT "B" INTO grad;
        SELECT 3.0 INTO gradePoint;
	ELSEIF TotalPerc >= 70 AND TotalPerc <= 73 THEN
		SELECT "B-" INTO grad;
        SELECT 2.67 INTO gradePoint;
	ELSEIF TotalPerc >= 66 AND TotalPerc <= 69 THEN
		SELECT "C+" INTO grad;
        SELECT 2.33 INTO gradePoint;
	ELSEIF TotalPerc >= 62 AND TotalPerc <= 65 THEN
		SELECT "C" INTO grad;
        SELECT 2.0 INTO gradePoint;
	ELSEIF TotalPerc >= 58 AND TotalPerc <= 61 THEN
		SELECT "C-" INTO grad;
        SELECT 1.67 INTO gradePoint;
	ELSEIF TotalPerc >= 52 AND TotalPerc <= 57 THEN
		SELECT "D+" INTO grad;
        SELECT 1.33 INTO gradePoint;
	ELSEIF TotalPerc >= 50 AND TotalPerc <= 53 THEN
		SELECT "D" INTO grad;
        SELECT 1.0 INTO gradePoint;
	ELSE 
		SELECT "F" INTO grad;
	END IF;
	UPDATE `subject` SET `grade` = grad WHERE `regNo` = reg AND `subName` = subN;
	UPDATE `subject` SET `gradePoints` = gradePoint WHERE `regNo` = reg AND `subName` = subN;
    SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;

DELIMITER //
CREATE PROCEDURE `calculateGPA` (IN reg VARCHAR(100))
BEGIN
	DECLARE totalCreditHours DECIMAL(10, 2) DEFAULT 0;
	DECLARE creditPoints DECIMAL(10, 2) DEFAULT 0;
	DECLARE GPAa DECIMAL(10, 2) DEFAULT 0;
    SET SQL_SAFE_UPDATES = 0;
    SELECT sum(`creditHours` * `gradePoints`) INTO creditPoints FROM `subject` WHERE `regNo` = reg;
    SELECT sum(`creditHours`) INTO totalCreditHours FROM `subject` WHERE `regNo` = reg;
    SELECT (creditPoints / totalCreditHours) INTO GPAa;
    UPDATE `student` SET `GPA` = GPAa WHERE `regNo` = reg;
    SET SQL_SAFE_UPDATES = 1;
END //
DELIMITER ;