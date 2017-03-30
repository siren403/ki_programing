using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class MonsterCtrl : MonoBehaviour
{

    public enum MonsterState { idle, trace, attack, die }
    public MonsterState mState = MonsterState.idle;

    private Transform mPlayerTransform = null;
    private NavMeshAgent mNavAgent = null;
    private Animator mAnimator = null;

    public float mTraceDist = 10.0f;
    public float mAttackDist = 2.0f;

    private bool mIsDie = false;

    public GameObject PFBloodEffect = null;
    public GameObject PFBloodDecal = null;

    public int hp;

    // Use this for initialization
    void Start()
    {
        mPlayerTransform = GameObject.FindWithTag("Player").transform;
        mNavAgent = this.GetComponent<NavMeshAgent>();
        mAnimator = this.GetComponent<Animator>();

        //mNavAgent.destination = mPlayerTransform.position;
        StartCoroutine(this.CheckMonsterState());
        StartCoroutine(this.MonsterAction());

        hp = 100;
    }


    IEnumerator CheckMonsterState()
    {
        while(!mIsDie)
        {
            yield return new WaitForSeconds(0.2f);

            float dist = Vector3.Distance(mPlayerTransform.position, this.transform.position);

            if(dist <= mAttackDist)
            {
                mState = MonsterState.attack;
            }
            else if(dist <= mTraceDist)
            {
                mState = MonsterState.trace;
            }
            else
            {
                mState = MonsterState.idle;
            }
        }
    }
    IEnumerator MonsterAction()
    {
        while (!mIsDie)
        {
            switch (mState)
            {
                case MonsterState.idle:
                    mNavAgent.Stop();
                    mAnimator.SetBool("IsTrace", false);
                    break;
                case MonsterState.trace:
                    mNavAgent.destination = mPlayerTransform.position;
                    mNavAgent.Resume();
                    mAnimator.SetBool("IsAttack", false);
                    mAnimator.SetBool("IsTrace", true);
                    break;
                case MonsterState.attack:
                    mNavAgent.Stop();
                    mAnimator.SetBool("IsAttack", true);
                    break;
            }
            yield return null;
        }
    }

    void CreateBloodEffect(Vector3 pos)
    {
        GameObject blood1 = Instantiate(PFBloodEffect, pos, Quaternion.identity);
        Destroy(blood1, 2.0f);

        Vector3 decalPos = transform.position + (Vector3.up * 0.05f);
        Quaternion decalRot = Quaternion.Euler(90, 0, Random.Range(0, 360));

        GameObject blood2 = Instantiate(PFBloodDecal, decalPos, decalRot);
        float scale = Random.Range(1.5f, 3.5f);
        blood2.transform.localScale = Vector3.one * scale;

        Destroy(blood2, 5.0f);
    }

    private void OnCollisionEnter(Collision tCollision)
    {
        if(tCollision.gameObject.CompareTag("tagBullet"))
        {
            CreateBloodEffect(tCollision.transform.position);
            Destroy(tCollision.gameObject);
            mAnimator.SetTrigger("IsHit");
        }
    }

    void OnDamage(object[] _params)
    {
        Debug.Log(string.Format("Hit ray {0} : {1}", _params[0], _params[1]));

        CreateBloodEffect((Vector3)_params[0]);

        hp -= (int)_params[1];
        if(hp <= 0)
        {
            Debug.Log("monster die");
        }

        mAnimator.SetTrigger("IsHit");
    }
}
