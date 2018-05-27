<?php
/**
 * @author neeke@php.net
 * Date: 18/3/29 下午7:51
 */

const JSONNET_PHP_VERSION = 'v1.3.1';
const JSONNET_PHP_AUTHOR  = 'neeke@php.net';

const CODE_SUCCESS = 1000;
const CODE_ERROR   = 900;

/**
 * @return string
 */
function jsonnet_get_version()
{
    return JSONNET_PHP_VERSION;
}

function jsonnet_get_author()
{
    return JSONNET_PHP_AUTHOR;
}

class Jsonnet
{
    public function __construct()
    {
        #Jsonnet init
    }

    public function __destruct()
    {
        #Jsonnet destroy
    }

    /**
     * @param $file_path
     *
     * @return array
     * @throws Exception
     */
    static public function evaluateFile($file_path)
    {
        throw new Exception('Jsonnet::evaluateFile #error', CODE_ERROR);

        return array();
    }

    /**
     * @param $snippet_string
     *
     * @return array
     * @throws Exception
     */
    static public function evaluateSnippet($snippet_string)
    {
        throw new Exception('Jsonnet::evaluateSnippet #error', CODE_ERROR);

        return array();
    }

    /**
     * @param $file_path
     *
     * @return array
     * @throws Exception
     */
    static public function fmtFile($file_path)
    {
        throw new Exception('Jsonnet::fmtFile #error', CODE_ERROR);

        return array();
    }

    /**
     * @param $snippet_string
     *
     * @return array
     * @throws Exception
     */
    static public function fmtSnippet($snippet_string)
    {
        throw new Exception('Jsonnet::fmtSnippet #error', CODE_ERROR);

        return array();
    }

}