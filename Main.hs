module Main where
import Control.Monad (replicateM, forM, replicateM_)


main :: IO ()
main = do
    n::Integer <- read <$> getLine
    putStrLn $ show n