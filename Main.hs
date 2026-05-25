module Main where
import GHC.Base 

main :: IO ()
main = do
    n <- read <$> getLine
    putStrLn(show $ square $ add1  n)
    
square = flip (^) 2
add1 = (+) 1
got x = x == 5
