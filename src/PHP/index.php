<html>
	<head>
		<meta http-equiv="content-type" content="text/html; charset=utf-8" />
		<title>PostGreSQL et Php</title>
	</head>

	<body>
		<!-- Création de la connection et des variables -->
		<?php
			$dbHost = "localhost"; 	// En principe rien à modifier
			$dbName = "nom_base";		// le nom de la base
			$dbUser = "user_base";	// le user PostGreSQL à utiliser
			$dbPass = "pass_base";	// le mot de passe du user
			$dbQuery =  "select * from TABLE ;"; // la requête que vous souhaitez exécuter.
			$connectDB 		= pg_connect("host=$dbHost dbname=$dbName user=$dbUser password=$dbPass");			
			if (!$connectDB) {
				print("Connection failed.");
				exit;
			} 
			$result 	= pg_exec($connectDB,$dbQuery);
			$numrows 	= pg_num_rows($result);
		?>
			
		<table border="1">
			<!-- Tout ce qui se trouve sous cette ligne est à adapter en fonction de votre requête-->

			<!-- Les noms de colonnes du tableau à afficher -->
			<tr>
				<th>Id</th>
				<th>Ville</th>
				<th>Code postal</th>
			</tr>
			<?

				for($ri = 0; $ri < $numrows; $ri++) {
					echo "<tr>\n";
						$row = pg_fetch_array($result, $ri);
						/* Insérer ci-dessous les noms de colonnes tels que fournis par la base */
						echo " <td>", $row["num_v"], "</td>
								<td>", $row["nom_v"], "</td>
								<td>", $row["code_postal_v"], "</td>
						</tr>
					";
				}
				pg_close($connectDB);
				?>
		</table>
	</body>
</html>
