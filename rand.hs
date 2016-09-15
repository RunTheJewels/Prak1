import System.Random

write::[Double]->String
write [x] = show x
write (x:xs) = show x ++ " " ++ write xs

main = do
gen <- getStdGen 
--i <- read :: Int
putStrLn $ "10 9"
putStrLn $ write $ take 100 (randomRs (-10000000.0, 10000000.0) gen)
