using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class FireCtrl : MonoBehaviour
{

    public GameObject PFBullet = null;

    public Transform mFirePos = null;

    public MeshRenderer mMuzzleFlash = null;

    public AudioSource mAudioSource = null;

    private void Start()
    {
        mMuzzleFlash.enabled = false;
        mAudioSource = GetComponent<AudioSource>();
    }

    private void Update()
    {
        Debug.DrawRay(mFirePos.position, mFirePos.forward * 10.0f, Color.green);

        if(Input.GetMouseButtonDown(0))
        {
            Fire();

            RaycastHit hit;
            if (Physics.Raycast(mFirePos.position, mFirePos.forward, out hit, 10.0f))
            {
                if(hit.collider.CompareTag("MONSTER"))
                {
                    object[] _params = new object[2];
                    _params[0] = hit.point;
                    _params[1] = 20;
                    hit.collider.gameObject.SendMessage("OnDamage", _params, SendMessageOptions.DontRequireReceiver);
                }
            }
        }
    }
    private void Fire()
    {
        //CreateBullet();
        mAudioSource.PlayOneShot(mAudioSource.clip);
        StartCoroutine(this.ShowMuzzleFlash());
    }
    void CreateBullet()
    {
        Instantiate(PFBullet, mFirePos.position, mFirePos.rotation);
    }
    IEnumerator ShowMuzzleFlash()
    {
        mMuzzleFlash.enabled = true;
        yield return new WaitForSeconds(Random.Range(0.05f, 0.3f));
        mMuzzleFlash.enabled = false;
    }
}
