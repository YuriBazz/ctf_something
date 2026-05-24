module Main where

import Control.Monad

readInteger :: IO Integer
readInteger = read <$> getLine

main :: IO ()
main = do
    n <- readInteger
    arr <- replicateM (fromIntegral n) readInteger
    k <- readInteger
    replicateM_ (fromIntegral k) $ do
        line <- getLine
        let (pStr : indicesStr) = words line
            p = read pStr :: Integer
            indices = take (fromIntegral p) (map read indicesStr)
            s = sum [arr !! fromIntegral (i - 1) | i <- indices]
        print s