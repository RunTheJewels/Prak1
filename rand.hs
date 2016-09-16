import System.Random

write::[Double]->String
write [x] = show x
write (x:xs) = show x ++ " " ++ write xs

main = do
gen <- getStdGen 
--i <- read :: Int
putStrLn $ "2 5 "
putStrLn $ write $ take 90 (randomRs (-10000000.0, 10000000.0) gen)
