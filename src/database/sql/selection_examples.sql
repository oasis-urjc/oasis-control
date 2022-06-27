SELECT s_i.id, s_i.type_, s_m.value_, s_m.time_ from sensors_info s_i left join sensors_measurements s_m on s_i.id = s_m.sensor; 
SELECT s_i.id, s_i.type_, s_m.value_, s_m.time_ from sensors_info s_i left join sensors_measurements s_m on s_i.id = s_m.sensor WHERE s_i.type_='humedad'; # Solo humedad

SELECT s_i.id, s_i.type_, s_m.value_, s_m.time_ from sensors_info s_i right join sensors_measurements s_m on s_i.id = s_m.sensor;

SELECT s_i.id, s_i.type_, s_m.value_, s_m.time_ from sensors_info s_i inner join sensors_measurements s_m on s_i.id = s_m.sensor;

SELECT s_i.id, s_i.type_, s_m.value_, s_m.time_ from sensors_info s_i cross join sensors_measurements s_m;

SELECT count(id), sensor from sensors_measurements group by sensor;