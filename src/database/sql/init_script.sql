CREATE DATABASE Oasis;
# DROP DATABASE Oasis; # para ekiminar la base de datos
# DROP table sensors_measurements
use Oasis;

CREATE TABLE `SensorsInfo` (
  `id` int NOT NULL AUTO_INCREMENT,
  `plot` int NOT NULL,
  `type_` varchar(255) NOT NULL,
  `model_` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `SensorsMeasurements` (
  `id` int NOT NULL AUTO_INCREMENT,
  `value_` double NOT NULL,
  `time_` TIMESTAMP  DEFAULT CURRENT_TIMESTAMP NOT NULL,
  `sensor` int NOT NULL,
  PRIMARY KEY (`id`),
  FOREIGN KEY(sensor) references SensorsInfo(id)
);

INSERT INTO SensorsInfo (plot, type_, model_) values (1, 'humedad', 'YL-69');
INSERT INTO SensorsInfo (plot, type_, model_) values (1, 'luz', 'XD-80');
INSERT INTO SensorsInfo (plot, type_, model_) values (1, 'temperatura', 'DHT11');
SELECT * FROM SensorsInfo;

INSERT INTO SensorsMeasurements (value_, sensor) values (0,1);


